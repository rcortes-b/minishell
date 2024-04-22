/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:18:22 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/21 14:18:23 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/error.h"
#include "../../includes/builtins.h"
#include "../../includes/exec.h"

static int	check_main_arg(char *arg)
{
	int	i;

	i = -1;
	if (!arg[0])
		return (0);
	while (arg[++i])
	{
		if ((arg[i] < '0' || arg[i] > '9'))
			return (0);
	}
	return (1);
}

static int	exit_aux(t_exe *vars, int do_exec)
{
	if ((*vars->lst)->flags[1][0] == '*' && !(*vars->lst)->flags[1][1])
	{
		printf("exit\nbash:exit: too many arguments\n");
		return (0);
	}
	if (!check_main_arg((*vars->lst)->flags[1]) && do_exec == 1)
		handle_exit(vars, 255);
	if (do_exec == 1)
		handle_exit(vars, ft_atoi((*vars->lst)->flags[1]));
	return (1);
}

void	do_exit(t_exe *vars, int do_exec)
{
	if ((*vars->lst)->flags[1] && (*vars->lst)->flags[2])
	{
		if (((*vars->lst)->flags[1][0] == '?'
			|| (*vars->lst)->flags[1][0] == '*') && !(*vars->lst)->flags[1][1])
			printf("exit\nminishell:exit: too many arguments\n");
		else if (!check_main_arg((*vars->lst)->flags[1]))
		{
			printf("exit\nminishell: exit: numeric argument required\n");
			if (do_exec == 1)
				handle_exit(vars, 255);
		}
		else
			printf("exit\nbash:exit: too many arguments\n");
		return ;
	}
	else if ((*vars->lst)->flags[1])
	{
		if (!exit_aux(vars, do_exec))
			return ;
	}
	if (do_exec == 1)
	{
		printf("exit\n");
		handle_exit(vars, 0);
	}
}
