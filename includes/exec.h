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
} t_exe;

char	*execution(t_word **lst, t_operators *data, t_env **my_env);
int		cooking_execution(t_exe *vars);

//Heredoc
int		do_heredoc(t_word **lst, char *limiter, t_env **my_env);

//Waits
void	wait_childs(t_exe *vars, int child_nbr);

//Builtins
int		is_builtin(char *cmd);

//Redirects
t_word	**set_redirects(t_word **lst, t_operators *data, t_env **my_env);

void	ejecutar_cosas(t_exe *vars, t_word *cmd);
void	ejecutar_builtins(t_exe *vars, t_word *aux);

void	do_signal(void);

#endif

