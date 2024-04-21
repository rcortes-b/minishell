/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 10:40:11 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/21 10:40:12 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define READ_END 0
# define WRITE_END 1

# include "minishell.h"
# include "parse.h"

typedef struct s_exe
{
	t_word	**lst;
	t_env	**env;
	char	**path;
	pid_t	pid;
	int		fd[2];
	int		stdin_fd;
}	t_exe;

//Utils
char	*check_path(char **path, char *cmd);

//Execution
char	*execution(t_word **lst, t_operators *data, t_env **my_env);
int		cooking_execution(t_exe *vars);
void	ejecutar_cosas(t_exe *vars, t_word *cmd);

//Heredoc
int		do_heredoc(t_word **lst, char *limiter, t_env **my_env);

//Waits
void	wait_childs(t_exe *vars, int child_nbr);

//Builtins
int		is_builtin(char *cmd);

//Redirects
t_word	**set_redirects(t_word **lst, t_operators *data, t_env **my_env);
void	set_redirect_values(t_word **lst_ptr, t_word **aux,
			int *head_com, int *is_redirect);

void	ejecutar_cosas(t_exe *vars, t_word *cmd);
void	exec_builtins(t_exe *vars, t_word *aux, int do_exec);

//Wait to Childs
void	wait_childs(t_exe *vars, int child_nbr);

void	do_signal(void);

#endif