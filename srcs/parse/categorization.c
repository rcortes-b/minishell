/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   categorization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvallhon <mvallhon@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 12:59:07 by mvallhon          #+#    #+#             */
/*   Updated: 2024/03/21 18:31:58 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

static void	put_command(t_word **new, char **word)
{
	(*new)->com = *word;
	(*new)->flags = NULL;
}

static t_word	*new_word(char **words, int start, int end, t_operators *data)
{
	t_word	*new;
	int		i;

	new = (t_word *)malloc(sizeof (t_word));
	if (!new)
		return (NULL); //free_all & exit(status)
	if (!is_symbol(data, words[start][0]))
	{
		new->com = ft_strdup(words[start]);
		if (!new->com)
			return (NULL); //free_all & exit(status)
		new->flags = (char **)malloc(sizeof (char *) * (end - start + 2));
		if (!new->flags)
			return (NULL); //free_all & exit(status)
		i = -1;
		while ((start + (++i)) <= end)
			new->flags[i] = words[start + i];
		new->flags[i] = NULL;
	}
	else
		put_command(&new, &words[start]);
	new->next = NULL;
	return (new);
}

static void	wordadd_back(t_word **words, t_word *new_word)
{
	t_word	*temp;

	if (words)
	{
		if (*words == NULL)
			*words = new_word;
		else
		{
			temp = *words;
			while (temp->next)
				temp = temp->next;
			temp->next = new_word;
		}
	}
}

void	categorize(char **words, t_word **lst, t_operators *data)
{
	t_word	*n_word;
	int		start;
	int		end;

	start = 0;
	end = 0;
	while (words[end])
	{
		if (is_symbol(data, words[end][0]))
		{
			start = end;
			n_word = new_word(words, start, end, data);
			wordadd_back(lst, n_word);
			end++;
		}
		else
		{
			start = end;
			while (words[end] && !is_symbol(data, words[end][0]))
				end++;
			n_word = new_word(words, start, end - 1, data);
			wordadd_back(lst, n_word);
		}
	}
}
