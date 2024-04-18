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
#include "../../includes/error.h"

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

static char	*del_quotes(char *str, char *new_str)
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

char	*remove_quotes(char *str, char **split)
{
	char	lead;
	char	*new_comm;
	int		i;
	int		lead_counter;

	lead = 'x';
	lead_counter = 0;
	i = -1;
	while (str[++i])
	{
		while (str[i] && str[i] != '"' && str[i] != '\'')
			i++;
		if (str[i] == '\'' || str[i] == '"')
		{
			lead = str[i++];
			lead_counter++;
		}
		while (str[i] && str[i] != lead)
			i++;
	}
	new_comm = (char *)malloc(ft_strlen(str) - (lead_counter * 2) + 1);
	if (!new_comm)
		return (free_mem(split), NULL);
	return (del_quotes(str, new_comm));
}
