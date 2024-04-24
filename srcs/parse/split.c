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
					if (!iterate_quote(line, &i, line[i], 0))
						return (-1);
				i++;
			}
		}
		else
			i++;
	}
	return (counter);
}

static int	get_word_size(char *line, const char *set,
	int ind, t_operators *data)
{
	int	size;

	size = 0;
	while (line[ind])
	{
		if (is_symbol(data, line[ind]))
		{
			do_operator(line, &ind, data, &size);
			return (size);
		}
		else if (!ft_strchr(set, line[ind]))
		{
			while (!ft_strchr(set, line[ind]) && !is_symbol(data, line[ind]))
			{
				if (line[ind] == data->dquote || line[ind] == data->squote)
					if (!iterate_quote(line, &ind, line[ind], &size))
						return (-1);
				ind++;
				size++;
			}
			return (size);
		}
		ind++;
	}
	return (1);
}

static int	split_word(char *word, const char *set, char *line, int *ind)
{
	t_operators	data;
	int			i;

	init_data(&data, NULL);
	i = 0;
	while (line[*ind])
	{
		if (!split_word_symbol(&word, line, ind, &data))
			break ;
		else if (!ft_strchr(set, line[*ind]))
		{
			while (!ft_strchr(set, line[*ind]) && !is_symbol(&data, line[*ind]))
			{
				if (line[*ind] == data.dquote || line[*ind] == data.squote)
					if (!copy_quotes(word, line, &i, ind))
						return (0);
				word[i++] = line[(*ind)++];
			}
			word[i] = '\0';
			break ;
		}
		else
			(*ind)++;
	}
	return (1);
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
	init_data(&data, NULL);
	while (++counter < word_counter)
	{
		size = get_word_size(line, set, i, &data);
		if (size == -1)
			return (free_mem(split), NULL);
		split[counter] = malloc(sizeof(char) * size + 1);
		if (!split[counter])
			return (free_mem(split), NULL);
		if (!split_word(split[counter], set, line, &i))
			return (free_mem(split), NULL);
	}
	split[counter] = NULL;
	return (split);
}

char	**ft_split(char *line, const char *set, t_operators *data)
{
	char		**split;
	int			counter;

	counter = count_words(line, set, data);
	if (!counter || counter == -1)
		return (NULL);
	split = ft_calloc(sizeof(char *), counter + 1);
	if (!split)
		return (NULL);
	split = get_split(split, set, line, counter);
	if (!split)
		return (NULL);
	return (split);
}
