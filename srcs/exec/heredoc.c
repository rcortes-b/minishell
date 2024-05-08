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

static char	*expand_heredoc(t_env **lst_env, char *str, int index)
{
	char	*env_name;
	t_env	*env;
	char	*new_str;
	int		i;
	int		j;

	i = index + 1;
	j = 0;
	while (str[i])
	{
		iterate_expand(str, &j, i);
		env_name = ft_substr(str, i, j);
		if (!env_name)
			return (NULL);
		env = get_env(lst_env, env_name);
		if (!env)
			return (free(env_name), NULL);
		new_str = malloc(ft_strlen(str) + ft_strlen(env->value)
				- ft_strlen(env->key) - 1);
		if (!new_str)
			return (free(env_name), NULL);
		new_str = get_expanded(new_str, env, str, index);
		return (free(str), free(env_name), new_str);
	}
	return (NULL);
}

static char	*check_hdoc_expand(char **line, t_env **my_env, char *limiter)
{
	int	i;

	i = 0;
	while (*line && (*line)[i])
	{
		if ((*line)[i] == '$' && limiter[0] != '\'')
		{
			*line = expand_heredoc(my_env, *line, i);
			i = 0;
		}
		i++;
	}
	return (NULL);
}

static int	check_limiter(char *line, char *limiter)
{
	int		i;
	char	*new_limiter;

	i = 0;
	new_limiter = ft_strdup(limiter);
	if (new_limiter[0] == '\'' || new_limiter[0] == '"')
		new_limiter = delete_quotes(new_limiter, (char *)malloc(ft_strlen(new_limiter) - 1));
	while (new_limiter[i])
	{
		if (new_limiter[i] != line[i])
			return (free(new_limiter), 0);
		i++;
	}
	if (line[i] == '\0' && new_limiter[i] == '\0')
		return (free(new_limiter), 1);
	return (free(new_limiter), 0);
}

static void	handle_hdoc_child(char *line, char *limiter,
		int fd[2], t_env **my_env)
{
	close(fd[0]);
	signal(SIGINT, NULL);
	signal(SIGINT, handle_sighdoc);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			rl_replace_line("", 0);
			exit (0);
		}
		if (!*line)
			continue ;
		if (check_limiter(line, limiter))
			break ;
		check_hdoc_expand(&line, my_env, limiter);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		if (line)
			free(line);
	}
	if (line)
		free(line);
	close(fd[1]);
	exit (0);
}

int	do_heredoc(t_word **lst, char *limiter, t_env **my_env)
{
	pid_t	pid;
	char	*line;
	int		fd[2];

	if (!*lst)
		return (0);
	line = NULL;
	if (pipe(fd) == -1)
		return (0);
	pid = fork();
	if (pid == 0)
		handle_hdoc_child(line, limiter, fd, my_env);
	close(fd[1]);
	if (wait_hdoc())
		return (close(fd[0]),(*lst)->in = -1, 0);
	(*lst)->in = fd[0];
	return (1);
}
