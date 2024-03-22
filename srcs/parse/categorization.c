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