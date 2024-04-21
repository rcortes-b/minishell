/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:25:11 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/21 14:25:12 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"
#include "../../includes/builtins.h"
#include "../../includes/error.h"

void	set_oldpwd(t_env **lst_env, int *is_oldpwd)
{
	t_env	*aux;

	aux = *lst_env;
	while (aux)
	{
		if (ft_strcmp(aux->key, "OLDPWD") == 0)
		{
			*is_oldpwd = 1;
			return ;
		}
		aux = aux->next;
	}
}

int	update_value(t_env **aux, char *value, int i)
{
	if ((*aux)->value)
		free((*aux)->value);
	(*aux)->value = ft_strdup(&value[i + 1]);
	if (!(*aux)->value)
		return (0);
	return (1);
}

void	check_value(char *value, int *i, int *is_append)
{
	*is_append = 0;
	while (value[++(*i)] && (value[*i] != '='
			|| (value[*i] != '+' && value[*i + 1] == '=')))
	{
		if (value[*i] == '+' && value[*i + 1] == '=')
		{
			*is_append = 1;
			break ;
		}
	}
}

t_env	*prepare_node(char *value, int is_onlyexp, int *i)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->only_exp = is_onlyexp;
	new->next = NULL;
	*i = 0;
	while (value[*i] && value[*i] != '=' && value[*i] != '+')
		(*i)++;
	new->key = ft_substr(value, 0, *i);
	if (!new->key)
		return (free(new), NULL);
	return (new);
}
