/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:00:12 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/05 13:00:13 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

void	iterate_expand(char *str, int *j, int i)
{
	while (str[i + *j] && str[i + *j] != '$'
		&& str[i + *j] != '"' && str[i + *j] != '\'' && str[i + *j] != ' ')
		(*j)++;
}

int	aux_lead(char lead, char ***split, char **str)
{
	if (lead == 'x')
	{
		*split = resplit(str, split);
		if (!*split)
			return (0);
	}
	return (1);
}

char	*invalid_env(char **str, char **env_name)
{
	char	*new_str;

	free(*env_name);
	new_str = (char *)malloc(sizeof(char));
	if (!new_str)
		return (NULL);
	*new_str = '\0';
	free(*str);
	return (new_str);
}