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

/*static void	set_ins(t_exe *vars)
{
	if ((*vars->lst)->next != NULL)
	{
		if ((*vars->lst)->next->in != -2)
		{
			if ((*vars->lst)->next->in == -1)
			{
				close(vars->fd[WRITE_END]);
				dup2(vars->fd[READ_END], STDIN_FILENO);
				close(vars->fd[READ_END]);
			}
			else
			{
				dup2((*vars->lst)->next->in, STDIN_FILENO);
				close((*vars->lst)->next->in);
			}
		}
		else if ((*vars->lst)->next->in == -2)
		{
			close(vars->fd[WRITE_END]);
			dup2(vars->fd[READ_END], STDIN_FILENO);
			close(vars->fd[READ_END]);
		}
	}
}*/

/*static void	set_ins(t_exe *vars) set_ins (mal marti cree)
{
	if ((*vars->lst)->in != -2)
	{
		if ((*vars->lst)->in == -1)
		{
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
	else if ((*vars->lst)->in == -2)
	{
		close(vars->fd[WRITE_END]);
		dup2(vars->fd[READ_END], STDIN_FILENO);
		close(vars->fd[WRITE_END]);
	}
}*/

/*static void	set_outs(t_exe *vars)
{
	if ((*vars->lst)->out != -2) //Si hay outfile
	{
		if ((*vars->lst)->out == -1) //Si la lectura del outfile ha fallado
		{
			fprintf(stderr, "FILE NOT WORKING! :C\n"); // gestion de errores
			close(vars->fd[READ_END]);
			dup2(vars->fd[WRITE_END], STDOUT_FILENO);
			close(vars->fd[WRITE_END]);
		}
		else //Se redirige al file descriptor del outfile
		{
			fprintf(stderr, "FILE WORKING! EN FD-OUT: %p! :D\n", &(*vars->lst)->out);
			dup2((*vars->lst)->out, STDOUT_FILENO);
			close((*vars->lst)->out);
		}
	}
	else if ((*vars->lst)->out == -2)
	{
	//	*if (!((*vars->lst)->next))
	//	{
	//		
		//}
		//else
		if (((*vars->lst)->next))
		{
			close(vars->fd[READ_END]);
			dup2(vars->fd[WRITE_END], STDOUT_FILENO);
			close(vars->fd[WRITE_END]);
		}
	}
}*/

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
			fprintf(stderr, "FILE WORKING! EN FD-IN: %p! :D\n", &(*vars->lst)->in);
			dup2((*vars->lst)->in, STDIN_FILENO);
			close((*vars->lst)->in);
		}
	}
	/*if ((*vars->lst)->in == -2) //ejecutas el comando y lo mandas por un pipe
	{
		pipe(vars->fd);
		if (vars->last == 0)
		{
			dup2(vars->fd[1], STDOUT_FILENO);
			close(vars->fd[0]);
			close(vars->fd[1]);
		}
	}*/
	//else if ((*vars->lst)->out > -1) //ejecutas el comando mandandolo por el fd y sin pipe
}


int	cooking_execution(t_exe *vars)
{
	t_word	*aux;

	aux = *vars->lst;
	first_argument(vars);
//	aux = aux->next;
	while (aux)
	{
		if (aux->token != PIPE) //no es una pipe
		{
			if (ft_strncmp("env", (*vars->lst)->com, 4) == 0)
				print_env(*vars->env);
			/*if (aux->next != NULL)
				pipe(vars->fd);
			vars->pid = fork();
			if (vars->pid == 0)
			{
				set_outs(vars);
				//execve("/bin/ls", (*vars->lst)->flags, NULL);
			}
			else
			{
				int	status;
				wait(&status);
				fprintf(stderr, "WAIT ERROR: %d\n", status);
			}*/
		}
		aux = aux->next;
	}
	return (1);
}
