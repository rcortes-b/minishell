/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:27:55 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/11 11:27:56 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/parse.h"
#include "../../includes/error.h"

static char	**free_builtins(char ***builtins, int index)
{
	int	i;

	i = -1;
	while (++i < index)
		free((*builtins)[i]);
	free(*builtins);
	return (NULL);
}

static char	**allocate_builtin(char **builtin)
{
	builtin[0] = ft_strdup("echo");
	if (!builtin[0])
		return (free(builtin), NULL);
	builtin[1] = ft_strdup("cd");
	if (!builtin[1])
		return (free_builtins(&builtin, 1));
	builtin[2] = ft_strdup("pwd");
	if (!builtin[2])
		return (free_builtins(&builtin, 2));
	builtin[3] = ft_strdup("export");
	if (!builtin[3])
		return (free_builtins(&builtin, 3));
	builtin[4] = ft_strdup("unset");
	if (!builtin[4])
		return (free_builtins(&builtin, 4));
	builtin[5] = ft_strdup("env");
	if (!builtin[5])
		return (free_builtins(&builtin, 5));
	builtin[6] = ft_strdup("exit");
	if (!builtin[6])
		return (free_builtins(&builtin, 6));
	builtin[7] = NULL;
	return (builtin);
}

char	**create_builtins(void)
{
	char	**builtins;

	builtins = (char **)malloc(sizeof(char *) * 8);
	if (!builtins)
		return (NULL);
	builtins = allocate_builtin(builtins);
	if (!builtins)
		return (NULL);
	return (builtins);
}

int	is_builtin(char **builtins, char *cmd)
{
	int	i;

	i = -1;
	while (builtins[++i])
	{
		if (ft_strcmp(builtins[i], cmd) == 0)
			return (1);
	}
	return (0);
}
