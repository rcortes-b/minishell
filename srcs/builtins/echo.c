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

static int	is_newline(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (1);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (1);
	}
	return (0);
}

void	echo_builtin(t_word *word)
{
	int	i;
	int	is_flag;

	i = 1;
	is_flag = 0;
	if (!word->flags[i])
		return (write(1, "\n", 1), (void)0);
	while (!is_newline(word->flags[i]))
	{
		is_flag = 1;
		i++;
	}
	while (word->flags[i])
	{
		write(1, word->flags[i], ft_strlen(word->flags[i]));
		if (word->flags[i + 1])
			write(1, " ", 1);
		else if (!word->flags[i + 1] && is_flag == 0)
			write(1, "\n", 1);
		i++;
	}
}
