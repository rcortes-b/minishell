/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:28:01 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/11 11:28:02 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char	**append_bar(char **split)
{
	char	**path;
	int		j;

	
	j = 0;
	while (split[j])
		j++;
	path = malloc(sizeof(char *) * (j + 1));
	if (!path)
		printf("Error.\n");
	j = -1;
	while (split[++j])
	{
		path[j] = ft_strjoin(split[j], "/");
		if (!path[j])
		{
			printf("Error.\n");
		}
		free(split[j]);
	}
	free(split);
	path[j] = NULL;
	return (path);
}


static char	**parse_path(t_env **my_env)
{
	t_env	*my_paths;
	char	**paths;
	int		i;

	my_paths = get_env(my_env, "PATH");
	i = 0;
	while (my_paths->value[i] != '/')
		i++;
	paths = ft_esplit(my_paths->value, ':');
	if (!paths)
	{
		ft_putendl_fd("utils.c Line 83: Malloc Error", 2);
		exit(EXIT_FAILURE); //cuidao, no exit
	}
	paths = append_bar(paths);
	return (paths);
}

char	*execution(t_word **lst, t_operators *data, t_env **my_env)
{
	t_exe	vars;

	vars.env = my_env;
	vars.lst = set_redirects(lst, data, my_env);
	if (!vars.lst)
	{
		printf("un poco kekw de tu parte\n");
		return (NULL); //si es void hay que comprobar errores
	}
	vars.path = parse_path(my_env);
	if (!vars.path)
		printf("Error.\n");
	//if (!(*lst)->next && (ft_strcmp((*lst)->com, "cd") == 0))
	//	change_directory(&vars);
		///do exit o cd
	if (!(*lst)->next && is_builtin((*lst)->com) == 2)
			ejecutar_builtins(&vars, *lst);
	else
	{
		if (!cooking_execution(&vars))
			return (NULL); //handle error aqui
	}
	return (*vars.path); //return temporal
}
