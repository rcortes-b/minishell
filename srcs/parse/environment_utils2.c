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

int     ft_envsize(t_env *lst)
{
        int     counter;

        counter = 0;
        while (lst)
        {
            lst = lst->next;
            counter++;
        }
        return (counter);
}
