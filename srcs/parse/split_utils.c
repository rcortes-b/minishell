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

void	iterate_quote(char *line, int *index, char c, int *size)
{
	(*index)++;
	if (size)
		(*size)++;
	while (line[*index] && line[*index] != c)
	{
		(*index)++;
		if (size)
			(*size)++;
	}
	if (!line[*index])
	{
		fprintf(stderr, "MAL CLOSE QUOTING\n");
		exit(EXIT_FAILURE);
	}
}

void	copy_quotes(char *word, char *line, int *i, int *index)
{
	char	c;

	c = line[*index];
	word[(*i)++] = line[(*index)++];
	while (line[*index] && line[*index] != c)
		word[(*i)++] = line[(*index)++];
	if (!line[*index])
	{
		fprintf(stderr, "MAL CLOSE QUOTING\n");
		exit(EXIT_FAILURE);
	}
}

int	do_operator(char *line, int *index, t_operators *data, int *size)
{
	if (size)
		(*size)++;
	if (line[*index] == data->pipe)
		(*index)++;
	else if (line[*index] == data->reinput)
	{
		(*index)++;
		if (line[*index] == data->reinput)
		{
			if (size)
				(*size)++;
			(*index)++;
		}
	}
	else if (line[*index] == data->reoutput)
	{
		(*index)++;
		if (line[*index] == data->reoutput)
		{
			if (size)
				(*size)++;
			(*index)++;
		}
	}
	return (1);
}

int	split_word_symbol(char **word, char *line,
	int *index, t_operators *data)
{
	int	i;

	i = 0;
	if (is_symbol(data, line[*index]))
	{
		word[0][i++] = line[(*index)++];
		if ((data->reinput == line[*index] && data->reinput == line[*index - 1])
			|| (data->reoutput == line[*index]
				&& data->reoutput == line[*index - 1]))
			word[0][i++] = line[(*index)++];
		word[0][i] = '\0';
		return (0);
	}
	return (1);
}
