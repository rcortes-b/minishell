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

//SIGINT == 2
//SIGQUIT == 3

int	ambiguos_red(t_env **env, t_word *aux)
{
	t_env	*tmp;

	if (*aux->com == '<' && aux->com[1] == '<')
		return (0);
	tmp = get_env(env, &aux->next->com[1]);
	if (!tmp || (tmp && tmp->only_exp))
		return (1);
	return (0);
}

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
		exit(1);
	}
}
