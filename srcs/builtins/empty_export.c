/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:20:12 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/17 20:20:12 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"
#include "../../includes/builtins.h"
#include "../../includes/error.h"

int	key_is_valid(char *var)
{
	int	i;

	if (var[0] >= '0' && var[0] <= '9')
	{
		g_errstatus = 1;
		ft_putendl_fd("minishell: export: not valid identifier", 2);
		return (0);
	}
	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (var[i] == '+' && var[i + 1] == '=')
			return (1);
		if (!ft_isalnum(var[i]))
		{
			g_errstatus = 1;
			ft_putendl_fd("minishell: export: not valid identifier", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	print_export(t_env **env)
{
	t_env	*aux;

	aux = *env;
	while (aux)
	{
		if (ft_strcmp(aux->key, "_") != 0 && !aux->trigger_utils)
		{
			if (aux->only_exp)
				printf("declare -x %s\n", aux->key);
			else
				printf("declare -x %s=\"%s\"\n", aux->key, aux->value);
		}
		aux = aux->next;
	}
}

static void	ft_swap_env(t_env **aux, t_env **tmp)
{
	char	*str_aux;
	int		temp;

	str_aux = (*aux)->key;
	(*aux)->key = (*tmp)->key;
	(*tmp)->key = str_aux;
	str_aux = (*aux)->value;
	(*aux)->value = (*tmp)->value;
	(*tmp)->value = str_aux;
	temp = (*aux)->only_exp;
	(*aux)->only_exp = (*tmp)->only_exp;
	(*tmp)->only_exp = temp;
	temp = (*aux)->trigger_utils;
	(*aux)->trigger_utils = (*tmp)->trigger_utils;
	(*tmp)->trigger_utils = temp;
}

static void	sort_list(t_env **env)
{
	t_env	*aux;
	t_env	*tmp;
	int		i;

	i = 0;
	aux = *env;
	while (aux)
	{
		tmp = aux->next;
		while (tmp)
		{
			if (aux->key[0] > tmp->key[0])
				ft_swap_env(&aux, &tmp);
			else if (aux->key[0] == tmp->key[0])
			{
				i = 0;
				while (aux->key[i] == tmp->key[i])
					i++;
				if (aux->key[i] > tmp->key[i])
					ft_swap_env(&aux, &tmp);
			}
			tmp = tmp->next;
		}
		aux = aux->next;
	}
}

int	empty_export(t_env **lst_env)
{
	t_env	*exp;
	t_env	*new;
	int		is_oldpwd;

	exp = *lst_env;
	is_oldpwd = 0;
	set_oldpwd(lst_env, &is_oldpwd);
	if (!is_oldpwd)
	{
		new = ft_newenv();
		if (!new)
			return (handle_error(), 0);
		new->key = ft_strdup("OLDPWD");
		if (!new->key)
			return (handle_error(), 0);
		new->value = NULL;
		new->only_exp = 1;
		new->trigger_utils = 0;
		ft_envadd_back(&exp, new);
	}
	sort_list(&exp);
	print_export(&exp);
	return (1);
}
