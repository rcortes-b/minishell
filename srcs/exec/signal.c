#include "../../includes/exec.h"
#include "../../includes/parse.h"
#include "../../includes/error.h"

//SIGINT == 2
//SIGQUIT == 3

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
		g_errstatus = 1;
	}
}

void	handle_sighdoc(int sig)
{
	if (sig == SIGINT)
	{
		write(0, "\n", 1);
		exit(1);
	}
}