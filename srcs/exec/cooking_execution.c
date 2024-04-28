/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cooking_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:28:10 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/11 11:28:11 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/parse.h"
#include "../../includes/error.h"
#include "../../includes/exec.h"
#include "../../includes/builtins.h"

static int	first_argument(t_exe *vars, t_word **aux)
{
	if ((*vars->lst)->in != -2)
	{
		if ((*vars->lst)->in == -1)
		{
			if (pipe(vars->fd) == -1)
				return (handle_error(), 0);
			close(vars->fd[WRITE_END]);
			dup2(vars->fd[READ_END], STDIN_FILENO);
			close(vars->fd[READ_END]);
			*aux = (*aux)->next;
			g_errstatus = 1;
		}
		else
		{
			dup2((*vars->lst)->in, STDIN_FILENO);
			close((*vars->lst)->in);
		}
	}
	return (1);
}

void	set_ins(t_exe *vars, t_word **aux)
{
	if ((*aux)->next != NULL)
	{
		if ((*aux)->next->in != -2)
		{
			if ((*aux)->next->in == -1)
			{
				close(vars->fd[WRITE_END]);
				dup2(vars->fd[READ_END], STDIN_FILENO);
				close(vars->fd[READ_END]);
				*aux = (*aux)->next;
				g_errstatus = 1;
			}
			else
			{
				dup2((*aux)->next->in, STDIN_FILENO);
				close((*aux)->next->in);
			}
		}
		else if ((*aux)->next->in == -2)
		{
			close(vars->fd[WRITE_END]);
			dup2(vars->fd[READ_END], STDIN_FILENO);
			close(vars->fd[READ_END]);
		}
	}
}

int	set_outs(t_exe *vars, t_word *aux)
{
	if (aux->out != -2)
	{
		if (aux->out == -1)
		{
			close(vars->fd[READ_END]);
			dup2(vars->fd[WRITE_END], STDOUT_FILENO);
			close(vars->fd[WRITE_END]);
			return (g_errstatus = 1, 0);
		}
		else
		{
			dup2(aux->out, STDOUT_FILENO);
			close(aux->out);
		}
	}
	else if (aux->out == -2)
	{
		if ((aux->next))
		{
			close(vars->fd[READ_END]);
			dup2(vars->fd[WRITE_END], STDOUT_FILENO);
			close(vars->fd[WRITE_END]);
		}
	}
	return (1);
}

void	executor(t_exe *vars, t_word *cmd, char **og_env)
{
	char	*correct_path;

	if (ft_strchr(cmd->com, '/') || *cmd->com == '~')
	{
		if (*cmd->com == '~')
			cmd->com = parse_home(get_env(vars->env, "HOME"), &cmd->com);
		correct_path = cmd->com;
	}
	else
		correct_path = check_path(vars->path, cmd->com);
	if (!correct_path)
		exit(127);
	if (execve(correct_path, cmd->flags, og_env) == -1)
	{
		perror("minishell: ");
		exit(126);
	}
}

int	cooking_execution(t_exe *vars, char **og_env)
{
	t_word	*aux;
	int		counter;

	aux = *vars->lst;
	vars->stdin_fd = dup(STDIN_FILENO);
	counter = 0;
	if (!first_argument(vars, &aux))
		return (0);
	while (aux)
	{
		if (!cooking_execution_aux(vars, &aux, og_env, &counter))
			return (0);
		aux = aux->next;
	}
	wait_childs(vars, counter);
	dup2(vars->stdin_fd, STDIN_FILENO);
	return (1);
}
