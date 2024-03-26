/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:22:48 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/26 17:22:49 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

char	*del_quotes(char *str, char *new_str)
{
	char	lead;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			lead = str[i++];
			while (str[i] != lead)
				new_str[j++] = str[i++];
			i++;
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free(str);
	str = NULL;
	return (new_str);
}

char	*get_expanded(char *new_str, char *env, char *str, int index)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (++i < index)
		new_str[i] = str[i];
	j = 0;
	while (env[j] != '=')
		j++;
	j++;
	k = j + i;
	while (env[j])
		new_str[i++] = env[j++];
	j = 1;
	while (str[k])
		new_str[i++] = str[k++];
	new_str[i] = '\0';
	return (new_str);
}
