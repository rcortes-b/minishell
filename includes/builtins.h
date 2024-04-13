/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:22:11 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/26 17:22:11 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#define EXIT_CODE 256

# include "minishell.h"
# include "parse.h"

/*
echo && echo -n
cd (relative && abs path)
pwd
export
unset
env
exit
*/

//Echo
void	echo_builtin(t_word *word, int fd);

//Env
void	print_env(t_env *env);

//Export
void	empty_export(t_env **lst_env);
void	do_export(t_exe **vars);

#endif
