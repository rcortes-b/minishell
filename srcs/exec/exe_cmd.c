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
#include "../../includes/builtins.h"

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

void	ejecutar_cosas(t_exe *vars, t_word *cmd)
{
	char	*correct_path;

	if (ft_strchr(cmd->com, '/') || *cmd->com == '~')
	{
		if (*cmd->com == '~')
			cmd->com = parse_home(get_env(vars->env, "HOME"), &cmd->com);
		correct_path = cmd->com;
	}
	else
		correct_path = check_path(vars->path, cmd->com);
	printf("LOL %s\n", correct_path);
	if (execve(correct_path, cmd->flags, NULL) == -1)
	{
		fprintf(stderr, "minishell: ");
		perror(correct_path);
		exit(127);
	}
}
