/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvallhon <mvallhon@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:04:33 by mvallhon          #+#    #+#             */
/*   Updated: 2024/05/07 18:04:36 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"
#include "../../includes/error.h"

int	ft_envsize(t_env *lst)
{
	int	counter;

	counter = 0;
	while (lst)
	{
		lst = lst->next;
		counter++;
	}
	return (counter);
}

void	renew_env_aux(char **new_env, char **new_aux, t_env *env_aux, int *i)
{
	if (env_aux->value)
	{
		*new_aux = ft_strjoin_v3(*new_aux, env_aux->value);
		if (!new_aux)
			handle_error();
	}
	new_env[(*i)++] = *new_aux;
}
