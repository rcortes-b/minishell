/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:59:33 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/23 16:59:34 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/parse.h"
#include "../../includes/error.h"
#include "../../includes/builtins.h"

void	set_redirect_values(t_word **lst_ptr, t_word **aux,
	int *head_com, int *is_redirect)
{
	if (*head_com == 1)
		*lst_ptr = *aux;
	*head_com = 0;
	if (*(*aux)->com == '|')
	{
		*head_com = 1;
		if (*is_redirect)
			(*lst_ptr)->next = *aux;
		*is_redirect = 0;
	}
}

void	wait_childs(t_exe *vars, int child_nbr)
{
	int	status;

	while (child_nbr--)
	{
		if (vars->pid == waitpid(-1, &status, 0))
		{
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
				{
					write(2, "^C\n", 3);
					g_errstatus = status + 128;
				}
				if (WTERMSIG(status) == SIGQUIT)
				{
					write(2, "Quit 3\n", 7);
					g_errstatus = status + 128;
				}
				return ;
			}
			g_errstatus = WEXITSTATUS(status);
		}
	}
}

char	*check_path(char **path, char *cmd)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (path && path[i])
	{
		cmd_path = ft_strjoin(path[i], cmd);
		if (!cmd_path)
			ft_putstr_fd("minishell: command not found\n", 2);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		i++;
		free(cmd_path);
	}
	ft_putstr_fd("minishell: command not found\n", 2);
	return (NULL);
}

void	close_pipes(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

int	do_command(t_exe *vars, t_word **aux, char **og_env)
{
	if ((*aux)->next != NULL)
	{
		if (pipe(vars->fd) == -1)
			return (0);
	}
	vars->pid = fork();
	if (vars->pid == -1)
		return (handle_error(), close_pipes(vars->fd), 0);
	if (vars->pid == 0)
	{
		signal(SIGQUIT, NULL);
		if (set_outs(vars, *aux))
		{
			if (is_builtin((*aux)->com) == 1)
			{
				if (!exec_builtins(vars, *aux, 0))
					return (0);
			}
			else
			{
				executor(vars, *aux, og_env);
			}
		}
	}
	else
		set_ins(vars, aux);
	return (1);
}
