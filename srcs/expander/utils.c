/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:51:02 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/27 15:51:04 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/parse.h"
#include "../../includes/error.h"

int	*set_dquote_values(int *tab_counter, int *i, int *j, int *tab)
{
	*tab_counter = 0;
	*i = -1;
	*j = 0;
	if (!tab)
		return (NULL);
	return (tab);
}

void	init_delvalues(int *i, int *new_counter, char *lead, int *j)
{
	*i = 0;
	*new_counter = 0;
	*lead = 'x';
	*j = 0;
}
