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
			return (free_mem(path), free_mem(split), NULL);
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
		return (perror("minishell:"), free_env_mem(my_env), NULL);
	paths = append_bar(paths);
	if (!paths)
		return (perror("minishell:"), free_env_mem(my_env), NULL);
	return (paths);
}

void	execution(t_word **lst, t_operators *data, t_env **my_env)
{
	t_exe	vars;

	vars.env = my_env;
	vars.lst = set_redirects(lst, data, my_env);
	if (!vars.lst)
		return ;
	vars.path = parse_path(my_env);
	if (!vars.path)
		return ;
	if (!(*lst)->next && is_builtin((*lst)->com) == 2)
	{
		if (!exec_builtins(&vars, *lst, 1))
			handle_error();
	}
	else
		cooking_execution(&vars, data->og_env);
	free_mem(vars.path);
}
