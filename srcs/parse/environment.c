/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:22:55 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/02 17:58:49 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_env	*get_env(t_env **env_lst, char *get_key)
{
	t_env	*aux;
	
	aux = *env_lst;
	while (aux)
	{
		if (ft_strcmp(get_key, aux->key) == 0)
			return (aux);
		aux = aux->next;
	}
	return (NULL);
}

void	parse_environment(t_env **env_lst, char **envp)
{
	t_env	*aux;
	int		i;
	int		j;

	*env_lst = NULL;
	i = -1;
	while (envp[++i])
	{
		j = 0;
		aux = ft_newenv();
		while (envp[i][j] != '=')
			j++;
		aux->key = ft_substr(envp[i], 0, j);
		j++;
		aux->value = ft_substr(envp[i], j, ft_strlen(envp[i]));
		aux->only_exp = 0;
		ft_envadd_back(env_lst, aux);
	}
}
