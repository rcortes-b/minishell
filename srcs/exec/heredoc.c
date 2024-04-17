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
#include "../../includes/expander.h"
#include "../../includes/error.h"

static char	*check_hdoc_expand(char **line, t_env **my_env)
{
	int	i;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$')
		{
			*line = do_expand(my_env, *line, i);
			i = 0;
		}
		i++;
	}
	return (NULL);
}

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

int	do_heredoc(t_word **lst, char *limiter, t_env **my_env)
{
	char	*line;
	int		fd[2];

	if (!*lst)
		return (0);
	line = NULL;
	if (pipe(fd) == -1)
		return (0);
		//Throw error
	while (1) //expand de una variable de entorno
	{
		line = readline("> ");
		printf("Line: %s Limiter: %s\n", line, limiter);
		if (!line)
			continue ;
		if (check_limiter(line, limiter))
			break ;
		check_hdoc_expand(&line, my_env);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		//free(line);
	}
	//free(line);
	close(fd[1]);
	(*lst)->in = fd[0];
	return (1);
}

void	wait_childs(t_exe *vars, int child_nbr)
{
	int	status;

	while (child_nbr--)
	{
		if (vars->pid == waitpid(-1, &status, 0))
		{
			g_errstatus = WEXITSTATUS(status);
			fprintf(stderr, "child status: %d\n", g_errstatus);
			if (g_errstatus != 0)
			{
				//gestion errores
				fprintf(stderr, "child error: %d\n", g_errstatus);
			}
		}
	}
}
