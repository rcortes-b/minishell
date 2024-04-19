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

static void	first_argument(t_exe *vars)
{
	if ((*vars->lst)->in != -2)
	{
		if ((*vars->lst)->in == -1)
		{
			if (pipe(vars->fd) == -1)
				fprintf(stderr, "PIPE NOT WORKING! :C\n"); // gestion de errores
			close(vars->fd[WRITE_END]);
			dup2(vars->fd[READ_END], STDIN_FILENO);
			close(vars->fd[READ_END]);
		}
		else
		{
			dup2((*vars->lst)->in, STDIN_FILENO);
			close((*vars->lst)->in);
		}
	}
}

/*static void	set_ins(t_exe *vars, t_word *aux)
{
	if (aux->next != NULL)
	{
		if (aux->next->in != -2)
		{
			if (aux->next->in == -1)
			{
				close(vars->fd[WRITE_END]);
				dup2(vars->fd[READ_END], STDIN_FILENO);
				close(vars->fd[READ_END]);
			}
			else
			{
				dup2(aux->next->in, STDIN_FILENO);
				close(aux->next->in);
			}
		}
		else if (aux->next->in == -2)
		{
			fprintf(stderr, "set ins -2\n");
			close(vars->fd[WRITE_END]);
			dup2(vars->fd[READ_END], STDIN_FILENO);
			close(vars->fd[READ_END]);
		}
	}
}*/

static void	set_outs(t_exe *vars, t_word *aux)
{
	if (aux->out != -2)
	{
		if (aux->out == -1)
		{
			close(vars->fd[READ_END]);
			dup2(vars->fd[WRITE_END], STDOUT_FILENO);
			close(vars->fd[WRITE_END]);
		}
		else
		{
			fprintf(stderr, "set out 1, 2, 3 pasa\n");
			dup2(aux->out, STDOUT_FILENO);
			close(aux->out);
		}
	}
	else if (aux->out == -2)
	{
		if ((aux->next))
		{
			fprintf(stderr, "set out -2 pasa\n");
			close(vars->fd[READ_END]);
			dup2(vars->fd[WRITE_END], STDOUT_FILENO);
			close(vars->fd[WRITE_END]);
		}
	}
}

void	ejecutar_cosas(t_exe *vars, t_word *cmd)
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
	printf("LOL %s\n", correct_path);
	if (execve(correct_path, cmd->flags, NULL) == -1)
	{
		fprintf(stderr, "minishell: ");
		perror(correct_path);
		exit(127);
	}
}

int	cooking_execution(t_exe *vars)
{
	t_word	*aux;
	int		counter;

	aux = *vars->lst;
	vars->stdin_fd = dup(STDIN_FILENO);
	counter = 0;
	first_argument(vars);
	while (aux)
	{
		if (is_builtin(aux->com) == 2)
			exec_builtins(vars, aux, 0);
		else
		{
			if (aux->token != PIPE)
			{	
				counter++; //El counter estaba fuera y contaba la pipe como un counter++. Ta bien eso??
				if (aux->next != NULL)
					pipe(vars->fd);
				//vars->pid = fork();
				//if (vars->pid == 0)
				//{
					set_outs(vars, aux);
					if (is_builtin(aux->com) == 1)
						exec_builtins(vars, aux, 0);
					else
						ejecutar_cosas(vars, aux);
				//}
				//else
				//	set_ins(vars, aux);
			}
		}
		aux = aux->next;
	}
	printf("Wait Counter: %d\n", counter);
	wait_childs(vars, counter);
	dup2(vars->stdin_fd, STDIN_FILENO);
	return (1);
}
