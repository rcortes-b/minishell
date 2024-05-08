/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:59:44 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/23 16:59:45 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/parse.h"
#include "../../includes/error.h"

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
		ft_putstr_fd("^C\n", 2);
		g_errstatus = 1;
		exit(1);
	}
}
int	wait_hdoc(void)
{
	int	status;

	waitpid(-1, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) != SIGSTOP)
		{
			g_errstatus = 1;
			return (1);
		}
	}
	else if (WIFEXITED(status))
	{
		WEXITSTATUS(status);
		if (status)
		{
			g_errstatus = 1;
			return (1);
		}
	}	
	return (0);
}