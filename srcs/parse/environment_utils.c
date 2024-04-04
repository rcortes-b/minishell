/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvallhon <mvallhon@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:50:42 by mvallhon          #+#    #+#             */
/*   Updated: 2024/04/02 17:58:51 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_env	*ft_newenv(void)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->next = NULL;
	return (new);
}

void	ft_envadd_back(t_env **env_lst, t_env *new_env)
{
	t_env	*aux;

	if (!new_env)
		return ;
	if (*env_lst == NULL)
	{
		*env_lst = new_env;
		return ;
	}
	aux = *env_lst;
	while (aux->next != NULL)
		aux = aux->next;
	aux->next = new_env;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}