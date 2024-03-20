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

static int	get_word_size(char *line, const char *set,
	int index, t_operators *data)
{
	int	size;

	size = 0;
	while (line[index])
	{
		if (check_if_operator(data, line[index]))
		{
			size = is_operator(line, index, data);
			return (size);
		}
		else if (!ft_strchr(set, line[index]))
		{
			while (!ft_strchr(set, line[index])
				&& !check_if_operator(data, line[index]))
			{
				index++;
				size++;
			}
			return (size);
		}
		else
			index++;
	}
	return (0);
}

static void	split_word_aux(char **word, char *line,
	int *index, t_operators *data)
{
	int	i;

	i = 0;
	if (data->squote == line[*index] || data->dquote == line[*index])
		get_word_quote(word, line, index, line[*index]);
	else
	{
		word[0][i++] = line[(*index)++];
		if ((data->reinput == line[*index] && data->reinput == line[*index - 1])
			|| (data->reoutput == line[*index]
				&& data->reoutput == line[*index - 1]))
			word[0][i++] = line[(*index)++];
		word[0][i] = '\0';
	}
}

static void	split_word(char *word, const char *set, char *line, int *index)
{
	t_operators	data;
	int			i;

	init_data(&data);
	i = 0;
	while (line[*index])
	{
		if (check_if_operator(&data, line[*index]))
		{
			split_word_aux(&word, line, index, &data);
			break ;
		}
		else if (!ft_strchr(set, line[*index]))
		{
			while (!ft_strchr(set, line[*index])
				&& !check_if_operator(&data, line[*index]))
				word[i++] = line[(*index)++];
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
		printf("Size: %d\n", size);
		split[counter] = malloc(sizeof(char) * size + 1);
		if (!split[counter])
		{
			free_mem(split);
			return (NULL);
		}
		split_word(split[counter], set, line, &i);
	}
	split[counter] = NULL;
	return (split);
}

char	**ft_split(char *line, const char *set)
{
	char		**split;
	t_operators	data;
	int			counter;

	init_data(&data);
	counter = count_words(line, set, &data);
	printf("Count Words: %d\n\n", counter);
	split = (char **)malloc(sizeof(char *) * (counter + 1));
	if (!split)
		return (NULL);
	split = get_split(split, set, line, counter);
	if (!split)
		free(split);
	printf("\n");
	return (split);
}

/*int main(void)
{
	char **split = ft_split(" \'\'c\"at\"\"dsa\"||ls \'>\'|> 0\"out\" ", " \t");
	for (int i = 0; split[i]; i++)
		printf("%s\n", split[i]);
}*/