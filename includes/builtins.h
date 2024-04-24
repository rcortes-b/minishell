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

# define EXIT_CODE 256

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
void	echo_builtin(t_word *word);

//Env
void	print_env(t_env *env);

//Export
int		empty_export(t_env **lst_env);
int		key_is_valid(char *var);
int		do_export(t_word *lst, t_exe **vars, int do_exec);
void	set_oldpwd(t_env **lst_env, int *is_oldpwd);
int		update_value(t_env **aux, char *value, int i);
void	check_value(char *value, int *i, int *is_append);
t_env	*prepare_node(char *value, int is_onlyexp, int *i);

//Pwd
void	print_pwd(t_env *env);
void	unset_env(t_env **env, char **values, int do_exec);

//Change Directory
int		change_directory(t_exe *vars, t_word *aux_ptr, int do_exec);
char	*parse_home(t_env *home, char **path);
char	*expand_oldpwd(t_exe *vars, char *flag);
int		exec_chdir(t_exe *vars, t_word **aux_ptr, char **old_pwd);
int		update_directory(t_env **env, char **old_pwd);

//Exit
void	do_exit(t_exe *vars, int do_exec);

#endif
