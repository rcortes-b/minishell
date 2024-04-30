/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
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

char	*expand_oldpwd(t_exe *vars, char *flag)
{
	t_env	*tmp;

	if (!(*flag == '-' && !flag[1]))
		return (flag);
	tmp = get_env(vars->env, "OLDPWD");
	if (!tmp || (tmp && !tmp->value))
	{
		free(flag);
		flag = NULL;
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		return (NULL);
	}
	free(flag);
	flag = ft_strdup(tmp->value);
	if (!flag)
		return (perror("minishell"), NULL);
	printf("%s\n", flag);
	return (flag);
}

int	exec_chdir(t_exe *vars, t_word **aux_ptr, char **old_pwd)
{
	if (chdir((*aux_ptr)->flags[1]) == 0)
	{
		if (!update_directory(vars->env, old_pwd))
			return (free(*old_pwd), 0);
	}
	else
		free(*old_pwd);
	return (1);
}
