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

void	update_env(t_env **aux, t_env **del_node)
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

	aux = *env;
	is_last = 0;
	while (aux->next)
	{
		i = 0;
		while (values[++i])
		{
			if (ft_strcmp(aux->next->key, values[i]) == 0 && do_exec == 1)
			{
				update_env(&aux, &aux->next);
				is_last = 1;
				break ;
			}
		}
		if (is_last)
			is_last = 0;
		else
			aux = aux->next;
	}
}
