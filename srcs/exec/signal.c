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
#include "../../includes/expander.h"

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
int	special_expand(t_env **env, char **split, int index, int trigg)
{
	t_env	*aux;
	char	*aux_split;
	int		lead_counter;
	int	i;
	int	j;

	aux_split = NULL;
	if (index > 0 && trigg == 1 && (!(*split[index - 1] == '<' || *split[index - 1] == '>')))
		return (0);
	i = 0;
	lead_counter = 0;
	while (split[index][i])
	{
		if (split[index][i] == '"')
		{
			i++;
			while (split[index][i] != '"')
			{
				if (split[index][i] != ' ')
					return (0);
				i++;
			}
			i++;
		}
		if (split[index][i] != '\'' || split[index][i + 1] != '$')
			return (0);
		i += 2;
		j = 0;
		iterate_expand(split[index], &j, i);
		aux = get_env(env, ft_substr(split[index], i, j));
		if (aux)
			return (0);
		lead_counter++;
		i += j;
		if (split[index][i] != '\'')
			return (0);
		i++;
	}
	if (!trigg)
	{
		aux_split = malloc(ft_strlen(*split) - (lead_counter * 2) + 1);
		*split = delete_quotes(*split, aux_split);
	}
	return (1);
}
