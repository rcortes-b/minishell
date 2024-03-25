/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:28:44 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/22 12:28:44 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

void	tokenization(t_word **lst, t_operators *data)
{
	t_word	*aux;

	aux = *lst;
	while (aux)
	{
		if (!is_symbol(data, aux->com[0]))
			aux->token = COMMAND;
		else if (aux->com[0] == data->pipe)
			aux->token = PIPE;
		else
		{
			if (aux->com[1])
			{
				if (data->reinput == aux->com[0])
					aux->token = HEREDOC;
				else
					aux->token = APPEND_OPT;
			}
			else if (aux->com[0] == data->reinput)
				aux->token = REINPUT;
			else
				aux->token = REOUTPUT;
		}
		aux = aux->next;
	}
}
