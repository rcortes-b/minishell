/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:32:22 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/20 17:32:23 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	check_if_operator(t_operators *data, char c)
{
	if (c == data->pipe || c == data->squote
		|| c == data->dquote || c == data->reinput || c == data->reoutput)
		return (1);
	return (0);
}

void	free_mem(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

int	is_operator(char *line, int index, t_operators *data)
{
	int		i;
	char	c;

	i = 1;
	c = line[index];
	if (data->pipe == line[index])
		return (i);
	else if (data->squote == line[index] || data->dquote == line[index])
	{
		index++;
		while (line[index++] != c)
			i++;
		i++;
	}
	else if (data->reinput == line[index])
	{
		if (line[index + 1] == data->reinput)
			i++;
	}
	else if (data->reoutput == line[index])
	{
		if (line[index + 1] == data->reoutput)
			i++;
	}
	return (i);
}

void	get_word_quote(char **word, char *line, int *index, char c)
{
	int	i;

	i = 0;
	word[0][i++] = c;
	(*index)++;
	while (line[*index] != c)
		word[0][i++] = line[(*index)++];
	word[0][i++] = line[(*index)++];
	word[0][i] = '\0';
}
