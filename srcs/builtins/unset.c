/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:18:23 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/17 20:18:23 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"
#include "../../includes/builtins.h"
#include "../../includes/error.h"

static void	unset_node_ptr(t_env **env, char **values)
{
	t_env	*tmp;
	int		i;

	i = -1;
	while (values[++i])
	{
		if (ft_strcmp((*env)->key, values[i]) == 0)
		{
			tmp = (*env)->next;
			free((*env)->key);
			if ((*env)->value)
				free((*env)->value);
			free(*env);
			*env = tmp;
			i = -1;
		}
	}
}

static void	update_env(t_env **aux, t_env **del_node)
{
	t_env	*tmp;

	tmp = (*del_node)->next;
	free((*del_node)->key);
	free((*del_node)->value);
	free(*del_node);
	(*aux)->next = tmp;
}

void	unset_env(t_env **env, char **values, int do_exec)
{
	t_env	*aux;
	int		is_last;
	int		i;

	is_last = 0;
	unset_node_ptr(env, values);
	aux = *env;
	while (aux->next)
	{
		i = 0;
		while (values[++i])
		{
			if (ft_strcmp(aux->next->key, values[i]) == 0
				&& do_exec == 1 && ft_strcmp("_", values[i]) != 0)
			{
				is_last = 1;
				update_env(&aux, &aux->next);
				break ;
			}
		}
		if (is_last)
			is_last = 0;
		else
			aux = aux->next;
	}
}
