/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:23:24 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/26 17:23:25 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"
#include "../../includes/checker.h"
#include "../../includes/error.h"

static void	custom_error_checker(char **words, char *c2, t_operators *data)
{
	ft_putstr_fd("syntax error near unexpected token ", 2);
	if (!c2)
		write(2, "'newline'", 9);
	else if (c2[0] == data->pipe)
		write(2, "'|'", 3);
	else if (c2[0] == data->reinput)
		write(2, "'<'", 3);
	else if (c2[0] == data->reoutput)
		write(2, "'>'", 3);
	write(2, "\n", 1);
	free_mem(words);
	exit(EXIT_FAILURE);
}

void	check_tokens(char **words, t_operators *data)
{
	int	op_counter;
	int	i;

	if (words[0][0] == data->pipe || words[0][0] == data->reoutput)
		custom_error_checker(words, words[0], data);
	op_counter = 0;
	i = -1;
	while (words[++i])
	{
		if (is_symbol(data, words[i][0]))
		{
			if (op_counter == 1) 
				custom_error_checker(words, words[i], data);
			op_counter = 1;
		}
		else
			op_counter = 0;
		if (!words[i + 1] && is_symbol(data, words[i][0]))
			custom_error_checker(words, words[i + 1], data);
	}
}
