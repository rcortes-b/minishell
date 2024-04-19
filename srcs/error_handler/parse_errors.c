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
	perror("minishell: ");
	exit(errno);
}

void	free_mem(char **split)
{
	int	i;

	i = -1;
	if (split)
	{
		if (*split)
		{
			while (split[++i])
			{
				free(split[i]);
				split[i] = NULL;
			}
		}
		free(split);
		split = NULL;
	}
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

void	handle_expand_error(t_env **lst_env)
{
	free_env_mem(lst_env);
	handle_error();
}

void	handle_env_error(t_env **lst_env, char **split)
{
	free_env_mem(lst_env);
	free_mem(split);
	handle_error();
}

void	handle_exit(t_exe *vars, int is_error)
{
	free_mem(vars->path);
	free_env_mem(vars->env);
	free_struct_nodes(vars->lst);
	if (is_error == 1)
		perror("minishell: ");
	exit(errno);
}
