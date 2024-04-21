/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:56:39 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/04 11:56:40 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"
# include "parse.h"
# include "exec.h"

//General Error
void	handle_exit(t_exe *vars, int err_code);

//Environment
void	free_env_mem(t_env **lst_env);
void	handle_env_error(t_env **lst_env, char **split);
void	handle_expand_error(t_env **lst_env);

//Split
void	free_mem(char **split);
void	handle_split_error(char **split);

//Main Struct
void	free_struct_nodes(t_word **words);

//Throw Error
void	handle_error(void);

//Free Node of Word Struct
void	free_word_node(t_word **lst);

#endif
