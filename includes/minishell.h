#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

enum operators
{
	pipe,
	squote,
	dquote,
	reinput,
	reoutput,
	heredoc,
	appoutput
};


#endif