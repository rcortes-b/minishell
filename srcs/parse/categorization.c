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
#include "../../includes/error.h"

static void	put_command(t_word **new, char **word)
{
	(*new)->com = *word;
	(*new)->flags = NULL;
}

static t_word	*new_word(char **words, int start, int end)
{
	t_word	*new;
	int		i;

	new = (t_word *)malloc(sizeof (t_word));
	if (!new)
		return (NULL);
	if (!is_operator(words[start], 0))
	{
		new->com = ft_strdup(words[start]);
		if (!new->com)
			return (free(new), NULL);
		new->flags = (char **)malloc(sizeof (char *) * (end - start + 2));
		if (!new->flags)
			return (free(new->com), free(new), NULL);
		i = -1;
		while ((start + (++i)) <= end)
			new->flags[i] = words[start + i];
		new->flags[i] = NULL;
	}
	else
		put_command(&new, &words[start]);
	new->in = -2;
	new->out = -2;
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

static t_word	*aux_categorize(char **words, int *start,
	int *end)
{
	t_word	*n_word;

	if (is_operator(words[*end], 0))
	{
		*start = *end;
		n_word = new_word(words, *start, *end);
		if (!n_word)
			return (NULL);
		(*end)++;
	}
	else
	{
		*start = *end;
		while (words[*end] && !is_operator(words[*end], 0))
			(*end)++;
		n_word = new_word(words, *start, ((*end) - 1));
		if (!n_word)
			return (NULL);
	}
	return (n_word);
}

int	categorize(char **words, t_word **lst)
{
	t_word	*n_word;
	int		start;
	int		end;

	start = 0;
	end = 0;
	while (words[end])
	{
		n_word = aux_categorize(words, &start, &end);
		if (!n_word)
		{
			free_struct_nodes(lst);
			handle_error();
			return (0);
		}
		wordadd_back(lst, n_word);
	}
	return (1);
}
