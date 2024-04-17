#include "../../includes/exec.h"
#include "../../includes/parse.h"
#include "../../includes/error.h"

//SIGINT == 2
//SIGQUIT == 3

static void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
		g_errstatus = 1;
	}
	else if (signal == SIGKILL)
		return ;
}


void	do_signal(void)
{
	struct sigaction	sa;

	sa.__sigaction_u.__sa_handler = &handle_signal;
	
	sigaction(SIGINT, &sa, NULL);
}