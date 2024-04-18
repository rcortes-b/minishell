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


char	**parse_path(t_env **my_env)
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
	if (!(*lst)->next && is_builtin((*lst)->com) == 2)
			exec_builtins(&vars, *lst, 1);
	else
	{
		if (!cooking_execution(&vars))
			return (NULL); //handle error aqui
	}
	free_mem(vars.path);
	return (*vars.path); //return temporal
}
