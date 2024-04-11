/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:28:28 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/11 11:28:28 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/parse.h"
#include "../../includes/error.h"

/*char	*check_path(char **path, char *cmd)
{
	int		i;
	int		fd;
	char	*cmd_path;

	i = 0;
	while (path[i])
	{
		cmd_path = ft_strjoin(path[i], cmd);
		if (!cmd_path)
			do_error(path, "utils.c Line 104: Malloc Error", -2);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		i++;
		free(cmd_path);
	}
	do_error(path, "utils.c Line 111: Command not found\n", -7);
	return (NULL);
}

void	ejecutar_cosas()
{
	t_temp	utils;

	if (pipe(data->fd) == -1)
		do_error(data->path, "pipex.c Line 39: Pipe Error:", -3);
	utils.pid = fork();
	if (utils.pid == -1)
		do_error(data->path, "pipex.c Line 42: Fork Error:", -4);
	else if (utils.pid == 0)
	{
		close(data->fd[READ_END]);
		dup2(data->fd[WRITE_END], STDOUT_FILENO);
		close(data->fd[WRITE_END]);
		utils.cmd = ft_split(argument, ' ');
		if (!utils.cmd)
			do_error(data->path, "pipex.c Line 50: Malloc Error.", -5);
		utils.cmd_path = check_path(data->path, utils.cmd[0]);
		if (execve(utils.cmd_path, utils.cmd, NULL) == -1)
			do_error(data->path, "pipex.c Line 53: Exec Error:", -6);
	}
	else
	{
		close(fd[WRITE_END]);
		dup2(fd[READ_END], STDIN_FILENO);
		close(fd[READ_END]);
	}
	set_ins();
	set_outs();
}
*/
