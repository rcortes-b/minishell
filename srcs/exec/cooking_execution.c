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


static void	set_ins(t_exe *vars, t_word *aux)
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
			fprintf(stderr, "aqui pasa\n");
			close(vars->fd[WRITE_END]);
			dup2(vars->fd[READ_END], STDIN_FILENO);
			close(vars->fd[READ_END]);
		}
	}
}

static void	set_outs(t_exe *vars, t_word *aux)
{
	if (aux->out != -2) //Si hay outfile
	{
		if (aux->out == -1) //Si la lectura del outfile ha fallado
		{
			//fprintf(stderr, "FILE NOT WORKING! :C\n"); // gestion de errores
			close(vars->fd[READ_END]);
			dup2(vars->fd[WRITE_END], STDOUT_FILENO);
			close(vars->fd[WRITE_END]);
		}
		else //Se redirige al file descriptor del outfile
		{
			fprintf(stderr, "aqui pasa\n");
			// fprintf(stderr, "FILE WORKING! EN FD-OUT: %p! :D\n", &(*vars->lst)->out);
			dup2(aux->out, STDOUT_FILENO);
			close(aux->out);
		}
	}
	else if (aux->out == -2)
	{
		if ((aux->next))
		{
			fprintf(stderr, "aqui pasa\n");
			close(vars->fd[READ_END]);
			dup2(vars->fd[WRITE_END], STDOUT_FILENO);
			close(vars->fd[WRITE_END]);
		}
	}
}

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
			//fprintf(stderr, "FILE WORKING! EN FD-IN: %p! :D\n", &(*vars->lst)->in);
			dup2((*vars->lst)->in, STDIN_FILENO);
			close((*vars->lst)->in);
		}
	}
	else if ((*vars->lst)->in == -2)
	{

	}
}


int	cooking_execution(t_exe *vars)
{
	t_word	*aux;
	int		fd;

	aux = *vars->lst;
	fd = dup(STDIN_FILENO);
	first_argument(vars);
//	aux = aux->next;
	while (aux)
	{
		if (ft_strcmp(aux->com, "export") == 0)
			do_export(aux, &vars);
		else if (ft_strcmp(aux->com, "env") == 0)
			print_env(*vars->env);
		else
		{
		if (aux->token != PIPE) //no es una pipe
		{
			if (aux->next != NULL)
				pipe(vars->fd);
			vars->pid = fork();
			if (vars->pid == 0)
			{
				set_outs(vars, aux);
				ejecutar_cosas(vars, aux);
			}
			else
			{
				set_ins(vars, aux);
			}
		}
		}
		aux = aux->next;
	}
	wait(NULL);
	wait(NULL);
	dup2(fd, STDIN_FILENO);
	return (1);
}
