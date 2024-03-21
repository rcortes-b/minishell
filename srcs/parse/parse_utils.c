/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:36:05 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/21 15:36:07 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int	is_symbol(t_operators *data, char c)
{
	if (c == data->reinput || c == data->reoutput || c == data->pipe)
		return (1);
	return (0);
}

void	init_data(t_operators *data)
{
	data->pipe = '|';
	data->squote = '\'';
	data->dquote = '"';
	data->reinput = '<';
	data->reoutput = '>';
}
