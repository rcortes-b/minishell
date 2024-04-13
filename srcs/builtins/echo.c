/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:26:54 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/26 17:26:55 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

/* La idea general: recibe fd (se le pasa 1 si va a terminal o se le pasa el fd[1] de la pipe para escribir ahi */
/* Se tiene en cuenta la unica flag que hay que tener en cuenta, la cual solo tiene posicion correcta despues del echo
posicion flags[1]. Y depende de si es la ultima palabra que escribir o no y si hay flag o no se escribe \n o nada :)  

     ******				ES UN PROTOTIPO, LUEGO HAY QUE AJUSTARLO AL CODIGO FINAL			******
	 ******								    NOT TESTED xd								    ******
*/

void	echo_builtin(t_word *word, int fd)
{
	int	i;
	int	is_flag;

	i = 1;
	if (ft_strcmp(word->flags[i], "-n") == 0)
	{
		is_flag = 1;
		i++;
	}
	else
		is_flag = 0;
	while (word->flags[i])
	{
		write(fd, word->flags[i], ft_strlen(word->flags[i]));
		if (word->flags[i + 1])
			write(fd, " ", 1);
		else if (!word->flags[i + 1] && is_flag == 0)
			write(fd, "\n", 1);
		i++;
	}
}