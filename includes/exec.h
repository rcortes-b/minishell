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
void	execution(t_word **lst, t_operators *data, t_env **my_env);
int		cooking_execution(t_exe *vars);
int		do_command(t_exe *vars, t_word **aux);
void	set_ins(t_exe *vars, t_word **aux);
int		set_outs(t_exe *vars, t_word *aux);
void	executor(t_exe *vars, t_word *cmd);
int		cooking_execution_aux(t_exe *vars, t_word **aux, int *counter);
void	del_redirect_nodes(t_word **word);

//Heredoc
int		do_heredoc(t_word **lst, char *limiter, t_env **my_env);

//Waits && Signals
void	wait_childs(t_exe *vars, int child_nbr);
void	handle_signal(int sig);
void	handle_sighdoc(int sig);

//Builtins
int		is_builtin(char *cmd);

//Redirects
t_word	**set_redirects(t_word **lst, t_operators *data, t_env **env);
void	set_redirect_values(t_word **lst_ptr, t_word **aux,
			int *head_com, int *is_redirect);
int		exec_builtins(t_exe *vars, t_word *aux, int do_exec);
int		ambiguos_redirect(t_env **env, t_word *aux);
t_word	*init_redirect_values(int *is_delete, int *head_com, int *is_redirect);
void	set_ambiguous_error(t_env **env, t_word *aux,
			t_word **lst_ptr, int *is_delete);
void	is_pipe(t_word *aux, int *is_delete);
void	set_redirect(int is_redirect, t_word **lst_ptr);
int		wait_hdoc(void);
void	aux_redirect(t_word **aux, t_word **tmp);

//Wait to Childs
void	wait_childs(t_exe *vars, int child_nbr);

//Pipes
void	close_pipes(int fd[2]);

#endif