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

# include "minishell.h"

/*
echo && echo -n
cd (relative && abs path)
pwd
export
unset
env    ***DONE***
exit
*/

void	echo_builtin(t_word *word, int fd);
void	print_env(char **envp);

#endif
