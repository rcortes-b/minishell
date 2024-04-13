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

static void	open_files(char *op, char *file_name, int is_pipe)
{
	int	fd;

	if (ft_strlen(op) > 2)
		ft_putstr_fd("near unexpected token lulw\n" ,2);
	fd = -2;
	if (*op == '>' && op[1] == '>' && !op[2])
		fd = open(file_name, O_CREAT | O_RDWR
				| O_APPEND, 0644);
	else if (*op == '<' && op[1] == '<' && !op[2])
		do_heredoc(NULL, file_name);
	else if (*op == '>')
		fd = open(file_name, O_CREAT | O_RDWR
				| O_TRUNC, 0644);
	else if (*op == '<')
		fd = open(file_name, O_RDONLY);
}

static void	do_redirects(char **split, int size, int is_pipe)
{
	char **new_split;
	int	i;

	new_split = malloc(sizeof(char *) * (size + 1));
	if (!new_split)
		return (NULL);
	i = -1;
	while (split[++i])
	{
		if (*split[i] == '<' || *split[i] == '>')
			open_files(split[i], split[i + 1], is_pipe);

	}
}

static int	check_main_arg(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
	}
	return (1);
}

void	do_exit(char **split)
{
	int	i;
	int	re_counter;
	int	is_pipe;

	i = -1;
	re_counter = 0;
	is_pipe = 0;
	while (split[++i])
	{
		if (*split[i] == '|' && !split[i][1])
			is_pipe = 1; //Hay una
		else if ((*split[i] == '<' || *split[i] == '>') && split[i][1])
			re_counter++;
		else if ((*split[i] == '<' || *split[i] == '>') && !split[i][1])
			handle_exit_error();
	}
	do_redirects(split, i - (re_counter * 2), is_pipe);
	if (!is_pipe)
		printf("exit\n");
	if ((i - (re_counter * 2)) > 2 )
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	}
}