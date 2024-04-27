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

int	is_quoted_operator(char *str)
{
	if (ft_strcmp(str, "\"|\"") == 0 || ft_strcmp(str, "\"<\"") == 0 || ft_strcmp(str, "\"<<\"") == 0 || ft_strcmp(str, "\">\"") == 0 || ft_strcmp(str, "\">>\"") == 0)
		return (1);
	return (0);
}

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

char	*prep_quotes(char *str, int index, t_exp *exp)//
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
		{
			if (i == index)
				exp->quote_amount = lead_counter;
			i++;
		}
		if (str[i] == '\'' || str[i] == '"')
		{
			lead = str[i++];
			lead_counter++;
		}
		while (str[i] && str[i] != lead)
		{
			if (i == index)
				exp->quote_amount = lead_counter;
			i++;
		}
	}
	new_comm = (char *)malloc(ft_strlen(str) - (lead_counter * 2) + 1);
	if (!new_comm)
		return (NULL);
	return (delete_quotes(str, new_comm));
}
