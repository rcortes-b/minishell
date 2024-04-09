#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "parse.h"

typedef struct s_exec
{
	int	fd[2];
	int	id;
} t_exec;

void	execution(t_word **lst, t_operators *data, t_env **my_env);
int		do_heredoc(t_word **lst, char *limiter);

#endif

