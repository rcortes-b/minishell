/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:20:03 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/17 20:20:04 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/builtins.h"
#include "../../includes/error.h"

static int	var_exists(t_env *env, char *value, int size)
{
	t_env	*aux;

	aux = env;
	while (aux)
	{
		if (ft_strncmp(aux->key, value, size) == 0)
			return (1);
		aux = aux->next;
	}
	return (0);
}

static int	new_var(t_env **env, char *value, int is_onlyexp, int is_append)
{
	t_env	*new;
	int		i;

	new = prepare_node(value, is_onlyexp, &i);
	if (!new)
		return (0);
	if (is_onlyexp)
	{
		new->value = (char *)malloc(sizeof(char));
		if (!new->value)
			return (free(new), free(new->key), 0);
		new->value[0] = '\0';
	}
	else
	{
		if (is_append)
			i += 2;
		else
			i++;
		new->value = ft_strdup(&value[i]);
		if (!new->value)
			return (free(new), free(new->key), 0);
	}
	ft_envadd_back(env, new);
	return (1);
}

static int	update_var(t_env **env, char *value, int is_append, int is_onlyexp)
{
	t_env	*aux;
	int		i;

	if (is_onlyexp)
		return (1);
	i = 0;
	while (value[i] != '=' && value[i] != '+')
		i++;
	aux = *env;
	while (ft_strncmp(aux->key, value, i) != 0)
		aux = aux->next;
	if (aux->only_exp)
		aux->only_exp = is_onlyexp;
	if (is_append)
	{
		aux->value = ft_strjoin(aux->value, &value[i + 2]);
		if (!aux->value)
			return (0);
	}
	else
	{
		if (!update_value(&aux, value, i))
			return (0);
	}
	return (1);
}

static int	add_export(t_env **env, char *value)
{
	int	is_onlyexp;
	int	is_append;
	int	is_new;
	int	i;

	i = -1;
	is_new = 1;
	is_onlyexp = 0;
	check_value(value, &i, &is_append);
	if (var_exists(*env, value, i))
		is_new = 0;
	if (!value[i])
		is_onlyexp = 1;
	if (is_new)
	{
		if (!new_var(env, value, is_onlyexp, is_append))
			return (0);
	}
	else
	{
		if (!update_var(env, value, is_append, is_onlyexp))
			return (0);
	}
	return (1);
}

int	do_export(t_word *lst, t_exe **vars, int do_exec)
{
	int	i;

	i = 0;
	if (!lst->flags[1] && do_exec == 1)
	{
		if (!empty_export((*vars)->env))
			return (free_mem((*vars)->path), 0);
	}
	else if (do_exec == 1)
	{
		while (lst->flags[++i])
		{
			if (lst->flags[i][0] == '_' && lst->flags[i][1] == '=')
				return (1);
			if (!key_is_valid(lst->flags[i]))
				return (0);
			else
			{
				if (!add_export((*vars)->env, lst->flags[i]))
					return (0);
			}
		}
	}
	return (1);
}
