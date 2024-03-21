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

void	categorize(char **words, t_word **lst, t_operators	*data)
{
	int		start;
	int		end;
	t_word	*n_word;

	start = 0;
	end = 0;
	while (1)
	{
		while (words[end + 1] && !is_symbol(data, words[end + 1][0]))
			end++;
		n_word = new_word(words, start, end);
		wordadd_back(lst, n_word);
		if (words[end + 1])
		{
			start = end + 1;
			end = start;
			n_word = new_word(words, start, end);
			wordadd_back(lst, n_word);
			start++;
			end++;
		}
		else
			break ;
	}
}
