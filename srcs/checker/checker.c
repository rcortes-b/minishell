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

#include "../../includes/checker.h"

void	check_tokens(char **words, t_operators *data)
{
	int	op_counter;
	int	i;

	if (words[0][0] == data->pipe || words[0][0] == data->reoutput) {
		printf("First is operator"); exit(EXIT_FAILURE);}//ret NULL, handle errpr
	op_counter = 0;
	i = -1;
	while (words[++i])
	{
		if (is_symbol(data, words[i][0]))
		{
			if (op_counter == 1) {
				printf("double operator, cuidaoo\n"); exit(EXIT_FAILURE);}//handle error
			op_counter = 1;
		}
		else
			op_counter = 0;
		if (!words[i + 1] && is_symbol(data, words[i][0])) {
			printf("Last is operator, lel\n"); exit(EXIT_FAILURE);}//handle error
	}
}
