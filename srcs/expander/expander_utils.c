/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 09:51:08 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/04 09:51:09 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/parse.h"

void	set_expand_values(char *lead, int *quote, char c, int value)
{
	*lead = c;
	*quote = value;
}

void	free_node(t_env **node)
{
	free((*node)->key);
	free((*node)->value);
	free(*node);
}
