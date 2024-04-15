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
# include "exec.h"

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
int		key_is_valid(char *var);
void	do_export(t_word *lst, t_exe **vars);

//Pwd
void	print_pwd(t_env *env);
void	unset_env(t_env **env, char **values);

#endif
