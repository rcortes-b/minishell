/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:59:30 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/04 11:59:31 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/error.h"

void	handle_error(void)
{
	perror("Error");
	exit(errno);
}

void	free_mem(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

void	handle_split_error(char **split)
{
	free_mem(split);
	handle_error();
}

void	free_env_mem(t_env **lst_env)
{
	t_env	*aux;
	t_env	*tmp;

	if (!*lst_env)
		return ;
	aux = *lst_env;
	while (aux)
	{
		if (aux->key)
			free(aux->key);
		if (aux->value)
			free(aux->value);
		tmp = aux->next;
		free(aux);
		aux = tmp;
	}
}

void	handle_env_error(t_env **lst_env, char **split)
{
	free_env_mem(lst_env);
	free_mem(split);
	handle_error();
}
