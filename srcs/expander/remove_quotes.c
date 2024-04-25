/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_remove_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:05:23 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/20 15:05:23 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/parse.h"
#include "../../includes/error.h"

static int	is_lead(char *str, char lead, int index)
{
	index += 1;
	while (str[index] && str[index] != lead)
	{
		if (str[index] == lead)
			return (1);
		index++;
	}
	if (!str[index])
		return (0);
	return (1);
}

static char	*delete_quotes(char *str, char *new_str)
{
	char	lead;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && is_lead(str, str[i], i))
		{
			lead = str[i++];
			while (str[i] && str[i] != lead)
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

static char	*prep_quotes(char *str)
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
		return (NULL);
	return (delete_quotes(str, new_comm));
}

int	remove_quotes(char **new_split)
{
	int	i;

	i = -1;
	while (new_split[++i])
	{
		if (!(ft_strcmp(new_split[i], "\"|\"") == 0)
			&& !(ft_strcmp(new_split[i], "\"<\"") == 0)
			&& !(ft_strcmp(new_split[i], "\"<<\"") == 0)
			&& !(ft_strcmp(new_split[i], "\">\"") == 0)
			&& !(ft_strcmp(new_split[i], "\">>\"") == 0))
		{
			new_split[i] = prep_quotes(new_split[i]);
			if (!new_split[i])
				return (0);
		}
	}
	return (1);
}
