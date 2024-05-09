/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:18:50 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/17 20:18:51 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/builtins.h"
#include "../../includes/error.h"

void	print_pwd(t_env **env)
{
	t_env	*aux;
	char	*pwd;

	aux = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		aux = get_env(env, "PWD");
		if (aux->value)
			printf("%s\n", aux->value);
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
	}
}
