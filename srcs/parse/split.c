/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:55:32 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/20 14:55:33 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"
#include "../../includes/error.h"

static int	count_words(char *line, const char *set, t_operators *data)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (line[i])
	{
		if (is_symbol(data, line[i]))
			counter += do_operator(line, &i, data, 0);
		else if (!ft_strchr(set, line[i]))
		{
			counter++;
			while (line[i] && !ft_strchr(set, line[i])
				&& !is_symbol(data, line[i]))
			{
				if (line[i] == data->dquote || line[i] == data->squote)
					iterate_quote(line, &i, line[i], 0);
				i++;
			}
		}
		else
			i++;
	}
	return (counter);
}

static int	get_word_size(char *line, const char *set,
	int index, t_operators *data)
{
	int	size;

	size = 0;
	while (line[index])
	{
		if (is_symbol(data, line[index]))
		{
			do_operator(line, &index, data, &size);
			return (size);
		}
		else if (!ft_strchr(set, line[index]))
		{
			while (!ft_strchr(set, line[index])
				&& !is_symbol(data, line[index]))
			{
				if (line[index] == data->dquote || line[index] == data->squote)
					iterate_quote(line, &index, line[index], &size);
				index++;
				size++;
			}
			return (size);
		}
		index++;
	}
	return (0);
}

static void	split_word(char *word, const char *set, char *line, int *index)
{
	t_operators	data;
	int			i;

	init_data(&data);
	i = 0;
	while (line[*index])
	{
		if (!split_word_symbol(&word, line, index, &data))
			break ;
		else if (!ft_strchr(set, line[*index]))
		{
			while (!ft_strchr(set, line[*index])
				&& !is_symbol(&data, line[*index]))
			{
				if (line[*index] == data.dquote || line[*index] == data.squote)
					copy_quotes(word, line, &i, index);
				word[i++] = line[(*index)++];
			}
			word[i] = '\0';
			break ;
		}
		else
			(*index)++;
	}
}

static char	**get_split(char **split, const char *set,
	char *line, int word_counter)
{
	t_operators	data;
	int			counter;
	int			size;
	int			i;

	counter = -1;
	i = 0;
	init_data(&data);
	while (++counter < word_counter)
	{
		size = get_word_size(line, set, i, &data);
		split[counter] = malloc(sizeof(char) * size + 1);
		if (!split[counter])
			handle_split_error(split);
		split_word(split[counter], set, line, &i);
	}
	split[counter] = NULL;
	return (split);
}

char	**ft_split(char *line, const char *set, t_operators *data)
{
	char		**split;
	int			counter;

	counter = count_words(line, set, data);
	split = (char **)malloc(sizeof(char *) * (counter + 1));
	if (!split)
		handle_error();
	split = get_split(split, set, line, counter);
	if (!split)
		free(split);
	printf("\n");
	return (split);
}
