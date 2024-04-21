/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:00:00 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/21 17:00:01 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

static void	order_flags(char **split, int checkpoint, int i, t_operators *data)
{
	char	*temp;
	int		aux;

	while (!is_symbol(data, split[checkpoint][0]))
		checkpoint++;
	i += 2;
	while (split[i] && !is_symbol(data, split[i][0]))
	{
		temp = split[i];
		aux = i;
		while (aux > checkpoint)
		{
			split[aux] = split[aux - 1];
			aux--;
		}
		split[checkpoint] = temp;
		checkpoint++;
		i++;
	}
}

static int	check_flag(char **split, int index, t_operators *data)
{
	int	i;

	i = 0;
	if (split[index + 1] && is_symbol(data, split[index + 1][0]))
		return (1);
	if (!split[index + 2])
		return (1);
	else if (split[index + 2][0] == data->pipe)
		return (1);
	return (0);
}

void	order_split(char **split, t_operators *data)
{
	int			i;
	int			checkpoint;

	i = -1;
	checkpoint = 0;
	while (split[++i])
	{
		if (data->pipe == split[i][0])
			checkpoint = i + 1;
		if (data->reinput == split[i][0] || data->reoutput == split[i][0])
		{
			if (!check_flag(split, i, data))
				order_flags(split, checkpoint, i, data);
		}
	}
}
