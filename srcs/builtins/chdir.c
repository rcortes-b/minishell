/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 14:47:23 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/21 14:47:24 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"
#include "../../includes/parse.h"
#include "../../includes/error.h"

static int	get_oldpwd(t_env **env, t_env **old, char **old_pwd)
{
	t_env	*new;

	if (!*old)
	{
		new = ft_newenv();
		if (!new)
			return (handle_error(), 0);
		new->key = ft_strdup("OLDPWD");
		if (!new->key)
			return (free(new), handle_error(), 0);
		new->value = *old_pwd;
		if (!new->value)
			return (free(new->key), free(new), handle_error(), 0);
		new->only_exp = 0;
		ft_envadd_back(env, new);
	}
	else
	{
		if ((*old)->value)
			free((*old)->value);
		(*old)->value = *old_pwd;
		(*old)->only_exp = 0;
	}
	return (1);
}

char	*parse_home(t_env *home, char **path)
{
	char	*new_path;

	new_path = ft_strdup(home->value);
	if (!new_path)
		return (handle_error(), NULL);
	new_path = ft_strjoin(new_path, &(*path)[1]);
	if (!new_path)
		return (handle_error(), NULL);
	free(*path);
	return (new_path);
}

static char	*is_absolute(t_exe *vars, char *path, int *is_relative)
{
	t_env	*aux;
	int		home_size;

	aux = get_env(vars->env, "HOME");
	home_size = ft_strlen(aux->value);
	if (path[0] == '~' && (path[1] == '/' || !path[1]))
	{
		path = parse_home(aux, &path);
		*is_relative = 0;
	}
	else if (ft_strncmp(aux->value, path, home_size) == 0
		&& (path[home_size] == '/' || !path[home_size]))
		*is_relative = 0;
	return (path);
}

static int	update_directory(t_env **env, char **old_pwd)
{
	t_env	*aux;
	t_env	*old;
	char	*tmp_pwd;

	aux = get_env(env, "PWD");
	tmp_pwd = ft_strdup(aux->value);
	if (!tmp_pwd)
		return (handle_error(), 0);
	free(aux->value);
	aux->value = getcwd(NULL, 0);
	if (!aux->value)
	{
		aux->value = ft_strdup(tmp_pwd);
		if (!aux->value)
			return (handle_error(), 0);
	}
	free(tmp_pwd);
	old = get_env(env, "OLDPWD");
	if (!get_oldpwd(env, &old, old_pwd))
		return (0);
	return (1);
}

int	change_directory(t_exe *vars, int do_exec)
{
	t_env	*aux;
	char	*old_pwd;
	int		is_relative;

	is_relative = 1;
	aux = get_env(vars->env, "PWD");
	old_pwd = ft_strdup(aux->value);
	if (!old_pwd)
		return (handle_error(), 0);
	(*vars->lst)->flags[1] = is_absolute(vars,
			(*vars->lst)->flags[1], &is_relative);
	if (access((*vars->lst)->flags[1], X_OK) != 0)
		return (free(old_pwd), handle_error(), 0);
	else if (do_exec == 1)
	{
		if (chdir((*vars->lst)->flags[1]) == 0)
		{
			if (!update_directory(vars->env, &old_pwd))
				return (free(old_pwd), 0);
		}
		else
			free(old_pwd);
	}
	return (1);
}
