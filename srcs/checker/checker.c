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

static int	custom_error_checker(char **words, char *c2,
	t_operators *data)
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
	g_errstatus = 258;
	return (-1);
}

int	check_tokens(char **words, t_operators *data)
{
	int	i;

	if (words[0][0] == data->pipe)
		return (custom_error_checker(words, words[0], data), 0);
	i = -1;
	while (words[++i])
	{
		if ((!words[i + 1] && is_symbol(data, words[i][0]))
		|| (*words[i] == data->reinput && *words[i + 1] == data->reinput)
			|| (*words[i] == data->reoutput && *words[i + 1] == data->reoutput))
			i = custom_error_checker(words, words[i + 1], data);
		if (words[i + 1])
		{
			if ((*words[i] == data->pipe && *words[i + 1] == data->pipe)
				|| (*words[i] == data->reinput
					&& *words[i + 1] == data->reoutput)
				|| (*words[i] == '<' && *words[i + 1] == '|')
				|| (*words[i] == '>' && *words[i + 1] == '<')
				|| (*words[i] == '>' && *words[i + 1] == '|'))
				i = custom_error_checker(words, words[i + 1], data);
		}
		if (i == -1)
			return (0);
	}
	return (1);
}
