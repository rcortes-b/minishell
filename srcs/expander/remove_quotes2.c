/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_remove_quotes2.c                               :+:      :+:    :+:   */
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

char	*del_quotes_expand(char *str, int lead_counter, t_exp *exp)//, int trigger)
{
	int		new_counter;
	char	*new;
	char	lead;
	int		i;
	int		j;

	//trigger = 0;
	new = malloc(ft_strlen(str) - (lead_counter * 2) + 1);
	if (!new)
		return (NULL);
	i = 0;
	new_counter = 0;
	lead = 'x';
	j = 0;
	while (str[i])
	{
		if (new_counter < lead_counter && !skip_quote(i, exp) && ((str[i] == '\''/* && !trigger*/) || str[i] == '"'))
		{
			new_counter++;
			lead = str[i++];
			while (str[i] != lead)
				new[j++] = str[i++];
		}
		else
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}

int	is_single_quote(char *str, int i, int index)
{
	if (str[i] == '"')
		return (0);
	i++;
	while (str[i] != '\'')
	{
		if (i >= index)
			return (1);
		i++;
	}
	return (0);
}

char	*rm_quotes_expand(t_exp *exp, char *str, int index)
{
	char	n_lead;
	int		i;
	int		lead_counter = 0;
	//int		trigger = 0;

	i = 0;
	n_lead = 'x';
	while (str[i] && i < index)
	{
		if (!skip_quote(i, exp) && !is_dquote(str, i, exp) && (str[i] == '\'' || str[i] == '"'))
		{
			//if (!(exp->is_split && str[i] == '\''))
			//{
				if (is_single_quote(str, i, index))
					break ;
				exp->quote_amount++;
				lead_counter++;
				n_lead = str[i++];
				while (str[i] != n_lead && i < index)
					i++;
		//	}
			//else
			//	trigger = 1;
		}
		i++;
	}
	if (lead_counter == 0)
		return (str);
	return (del_quotes_expand(str, lead_counter, exp));
}