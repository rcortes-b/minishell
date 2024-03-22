/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvallhon <mvallhon@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:03:25 by mvallhon          #+#    #+#             */
/*   Updated: 2024/03/21 18:21:36 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

//malloc de las flags con end - start + 1 (ambos inclusive) + 1 (NULL terminating)

t_word	*new_word(char **words, int start, int end, t_operators *data)
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
		new->flags = (char **)malloc(sizeof (char *) * (end - start + 1 + 1));
		if (!new->flags)
			return (NULL); //free_all & exit(status)
		i = -1;
		while ((start + (++i)) <= end)
			new->flags[i] = words[start + i];
		new->flags[i] = NULL;
	}
	else
	{
		new->com = words[start];
		new->flags = NULL;
	}
	new->next = NULL;
	return (new);
}

void	wordadd_back(t_word **words, t_word *new_word)
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
