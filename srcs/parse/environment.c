/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:22:55 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/26 15:22:56 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

char	*get_env(t_list **lst, char *key)
{
	t_list	*aux;
	int		i;

	aux = *lst;
	while (aux)
	{
		i = 0;
		while (key[i] && aux->content[i] && aux->content[i] == key[i])
			i++;
		if (!key[i] && aux->content[i] == '=')
			return (aux->content);
		aux = aux->next;
	}
	return (NULL);
}

void	parse_environment(t_list **lst, char **envp)
{
	t_list	*aux;
	int		i;

	*lst = NULL;
	i = -1;
	while (envp[++i])
	{
		aux = ft_lstnew(envp[i]);
		ft_lstadd_back(lst, aux);
	}
}
