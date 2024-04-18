/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:26:54 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/26 17:26:55 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	echo_builtin(t_word *word)
{
	int	i;
	int	is_flag;

	i = 1;
	if (ft_strcmp(word->flags[i], "-n") == 0)
	{
		is_flag = 1;
		i++;
	}
	else
		is_flag = 0;
	while (word->flags[i])
	{
		if (word->flags[i][0] == '$'
			&& word->flags[i][1] == '?' && !word->flags[i][2])
			ft_putnbr_fd(g_errstatus, 1);
		else
			write(1, word->flags[i], ft_strlen(word->flags[i]));
		if (word->flags[i + 1])
			write(1, " ", 1);
		else if (!word->flags[i + 1] && is_flag == 0)
			write(1, "\n", 1);
		i++;
	}
}
