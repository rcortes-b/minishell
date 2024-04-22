#include "../../includes/exec.h"
#include "../../includes/parse.h"
#include "../../includes/error.h"
#include "../../includes/builtins.h"

void	set_redirect_values(t_word **lst_ptr, t_word **aux,
	int *head_com, int *is_redirect)
{
	if (*head_com == 1)
		*lst_ptr = *aux;
	*head_com = 0;
	if (*(*aux)->com == '|')
	{
		*head_com = 1;
		if (*is_redirect)
			(*lst_ptr)->next = *aux;
		*is_redirect = 0;
	}
}

void	wait_childs(t_exe *vars, int child_nbr)
{
	int	status;

	while (child_nbr--)
	{
		if (vars->pid == waitpid(-1, &status, 0))
		{
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
				{
					write(2, "^C\n", 3);
					g_errstatus = status + 128;
				}
				if (WTERMSIG(status) == SIGQUIT)
				{
					write(2, "Quit 3\n", 7);
					g_errstatus = status + 128;
				}
				return ;
			}
			g_errstatus = WEXITSTATUS(status);
			fprintf(stderr, "child status: %d\n", g_errstatus);
			if (g_errstatus != 0)
			{
				//gestion errores
				fprintf(stderr, "child error: %d\n", g_errstatus);
			}
		}
	}
}

char	*check_path(char **path, char *cmd)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (path[i])
	{
		cmd_path = ft_strjoin(path[i], cmd);
		if (!cmd_path)
			fprintf(stderr, "exec_cmd.c Line 28: Malloc Error");
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		i++;
		free(cmd_path);
	}
	fprintf(stderr, "exec_cmd.c Line 34: Command not found\n");
	return (cmd);
}

void	close_pipes(int	fd[2])
{
	close(fd[0]);
	close(fd[1]);
}
