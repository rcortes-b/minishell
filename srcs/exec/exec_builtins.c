#include "../../includes/exec.h"
#include "../../includes/parse.h"
#include "../../includes/error.h"
#include "../../includes/builtins.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return(1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return(2);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return(1);
	else if (ft_strcmp(cmd, "export") == 0)
		return(2);
	else if (ft_strcmp(cmd, "unset") == 0)
		return(2);
	else if (ft_strcmp(cmd, "env") == 0)
		return(1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return(2);
	return (0);
}

void	exec_builtins(t_exe *vars, t_word *aux, int do_exec)
{
	if (ft_strcmp(aux->com, "export") == 0)
		do_export(aux, &vars, do_exec);
	else if (ft_strcmp(aux->com, "env") == 0)
		print_env(*vars->env);
	else if (ft_strcmp(aux->com, "unset") == 0)
		unset_env(vars->env, (*vars->lst)->flags, do_exec);
	else if (ft_strcmp(aux->com, "cd") == 0)
		change_directory(vars, do_exec);
	else if (ft_strcmp(aux->com, "exit") == 0)
		do_exit(vars, do_exec);
	else if (ft_strcmp(aux->com, "echo") == 0)
		echo_builtin(aux);
	else if (ft_strcmp(aux->com, "pwd") == 0)
		print_pwd(*vars->env);
	//if (is_builtin(aux->com) == 1) //Comentado para leaks check
	//	exit(0);
}
