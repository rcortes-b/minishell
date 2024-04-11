/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:28:14 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/11 11:28:15 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/parse.h"
#include "../../includes/error.h"

static int	check_limiter(char *line, char *limiter)
{
	int	i;

	i = 0;
	while (limiter[i])
	{
		if (limiter[i] != line[i])
			return (0);
		i++;
	}
	if (line[i] == '\0' && limiter[i] == '\0')
		return (1);
	return (0);
}

int	do_heredoc(t_word **lst, char *limiter)
{
	char	*line;
	int		fd[2];

	line = NULL;
	if (pipe(fd) == -1)
		return (0);
		//Throw error
	while (1)
	{
		line = readline(">");
		if (!line)
			continue ;
		if (check_limiter(line, limiter))
			break ;
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fd[1]);
	(*lst)->in = fd[0];
	return (1);
}
