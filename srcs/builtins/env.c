/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:04:39 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/03 12:04:40 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	print_env(t_env *env)
{
	t_env	*aux;

	aux = env;
	while (aux)
	{
		if (ft_strcmp(aux->key, "_") != 0 && !env->only_exp)
			printf("%s=%s\n", aux->key, aux->value);
		else
			printf("%s=/usr/bin/env\n", aux->key);
		aux = aux->next;
	}
}
