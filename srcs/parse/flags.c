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

/* Esta funcion termina de hacer el sorting, 
teniendo en cuenta el checkpoint (comando) y el indice (primer redirection) */

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

/* Condicionales para detectar si la funcion tiene que ordenar flags o no */

static int	check_flag(char **split, int index, t_operators *data)
{
	int	i;

	i = 0;
	if (split[index + 1] && is_symbol(data, split[index + 1][0]))
		return (1);
	if (!split[index + 2] || split[index + 2][0] == data->pipe)
		return (1);
	return (0);
}

/* Sirve para ordenar los flags. 
Por ejemplo: 'ls > out -l'  --> 'ls -l > out' */

void	order_split(char **split, t_operators *data)
{
	int			i;
	int			checkpoint;

	i = -1;
	checkpoint = 0;
	if (split[checkpoint][0] == data->reinput)
	{
		checkpoint++;
		i++;
	}
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
