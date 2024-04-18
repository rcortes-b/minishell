#include "../../includes/error.h"
#include "../../includes/builtins.h"
#include "../../includes/exec.h"

/* hay que comprobar que exit sea la unica estructura. El comando EXIT se ejecuta SOLO */
/* Puede ser una  comprobacion inicial si el primero es exit y argc es >  */

//exit solo es 0
//exit a es exit + error
//exit 5 es 5
//exit a 5 es exit + error
//exit 5 6 NO es exit y da error de too many args

//ojo con estos: > <

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
  

void	do_exit(t_exe *vars, int do_exec)
{
	if ((*vars->lst)->flags[1] && (*vars->lst)->flags[2])
	{
		if (((*vars->lst)->flags[1][0] == '?' || (*vars->lst)->flags[1][0] == '*') && !(*vars->lst)->flags[1][1])
			printf("exit.\nbash:exit: too many arguments\n");
		else if (!check_main_arg((*vars->lst)->flags[1]))
		{
			printf("bash: exit: numeric argument required");
			if (do_exec == 1)
				exit(255);
		}
		else
			printf("exit.\nbash:exit: too many arguments\n");
		return ;
	}
	else if ((*vars->lst)->flags[1])
	{
		if ((*vars->lst)->flags[1][0] == '*' && !(*vars->lst)->flags[1][1])
		{
			printf("exit.\nbash:exit: too many arguments\n");
			return ;
		}
		if (!check_main_arg((*vars->lst)->flags[1]) && do_exec == 1)
			exit(255);
		if (do_exec == 1)
			exit(ft_atoi((*vars->lst)->flags[1]));
	}
	if (do_exec == 1)
		handle_exit(vars, 0);
}