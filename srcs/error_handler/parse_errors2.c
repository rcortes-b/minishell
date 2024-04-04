/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:59:34 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/04 11:59:35 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/error.h"

void	free_struct_nodes(t_word **words)
{
	t_word	*aux;
	t_word	*tmp;
	int		i;

	if (!*words)
		return ;
	aux = *words;
	while (aux)
	{
		if (aux->com)
			free(aux->com);
		i = -1;
		if (aux->flags)
		{
			while (aux->flags[++i])
				free(aux->flags[i]);
			free(aux->flags);
		}
		tmp = aux->next;
		free(aux);
		aux = tmp;
	}
}
