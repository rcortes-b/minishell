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
	char	**builtins;
	pid_t	pid;
	int		fd[2];
} t_exe;

char	*execution(t_word **lst, t_operators *data, t_env **my_env);
int		cooking_execution(t_exe *vars);

//Heredod
int		do_heredoc(t_word **lst, char *limiter);

//Builtins
char	**create_builtins(void);
int		is_builtin(char **builtins, char *cmd);

//Redirects
t_word	**set_redirects(t_word **lst, t_operators *data);

#endif

