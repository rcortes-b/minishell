/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:22:22 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/02 18:07:34 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

char	*get_expanded(char *new_str, char *env, char *str, int index);
char	*del_quotes(char *str, char *new_str);
void	expand_cli(t_word **word, t_env **lst_env);

#endif
