/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:55:21 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/20 14:55:22 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

static void	iterate_quote(char *line, int *index, char c)
{
	(*index)++;
	while (line[*index] != c && line[*index])
		(*index)++;
	if (!line[*index])
	{
		fprintf(stderr, "MAL CLOSE QUOTING\n");
		exit(EXIT_FAILURE);
	}
	(*index)++;
}

static int	do_operator(char *line, int *index, t_operators *data)
{
	if (line[*index] == data->squote)
		iterate_quote(line, index, data->squote);
	else if (line[*index] == data->dquote)
		iterate_quote(line, index, data->dquote);
	else if (line[*index] == data->pipe)
		(*index)++;
	else if (line[*index] == data->reinput)
	{
		(*index)++;
		if (line[*index] == data->reinput)
			(*index)++;
	}
	else if (line[*index] == data->reoutput)
	{
		(*index)++;
		if (line[*index] == data->reoutput)
			(*index)++;
	}
	return (1);
}

int	count_words(char *line, const char *set, t_operators *data)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (line[i])
	{
		if (check_if_operator(data, line[i]))
		{
			counter += do_operator(line, &i, data);
			continue ;
		}
		else if (!ft_strchr(set, line[i]))
		{
			counter++;
			while (!ft_strchr(set, line[i])
				&& !check_if_operator(data, line[i]) && line[i])
				i++;
		}
		else
			i++;
	}
	return (counter);
}
