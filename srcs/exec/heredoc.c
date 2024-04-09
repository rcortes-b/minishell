#include "../../includes/exec.h"
#include "../../includes/parse.h"
#include "../../includes/error.h"

/*static int	check_limiter(char *line, char *argument)
{
	int	i;

	i = 0;
	while (argument[i])
	{
		if (argument[i] != line[i])
			return (0);
		i++;
	}
	if (line[i] == '\n' && argument[i] == '\0')
		return (1);
	return (0);
}

void	do_here_doc(t_data *data, char **arguments)
{
	char	*line;
	int		fd[2];

	if (pipe(fd) == -1)
		do_error(data->path, "here_doc.c Line: 21: Pipe Error:", -3);
	ft_putstr_fd("pipe heredoc> ", 1);
	line = NULL;
	while (1)
	{
		if (line)
			ft_putstr_fd("pipe heredoc> ", 1);
		line = get_next_line(0);
		if (!line)
			continue ;
		if (check_limiter(line, arguments[2]))
			break ;
		write(fd[WRITE_END], line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fd[WRITE_END]);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
}*/

static int	check_limiter(char *line, char *limiter)
{
	int	i;

	i = 0;
	while (limiter[i])
	{
		if (limiter[i] != line[i])
			return (0);
		i++;
	}
	if (line[i] == '\0' && limiter[i] == '\0')
		return (1);
	return (0);
}

int	do_heredoc(t_word **lst, char *limiter)
{
	char	*line;
	int		fd[2];

	line = NULL;
	if (pipe(fd) == -1)
		return (0);
		//Throw error
	while (1)
	{
		line = readline(">");
		if (!line)
			continue ;
		if (check_limiter(line, limiter))
			break ;
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fd[1]);
	(*lst)->in = fd[0];
	return (1);
}