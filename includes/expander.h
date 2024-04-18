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
# include "parse.h"

//char	*del_quotes(char *str, char *new_str);
void	free_node(t_env **node);
char	**expand_cli(char **words, t_env **lst_env);
char	**resplit(char **str, char ***split);
int		aux_lead(char lead, char ***split, char **str);
void	iterate_expand(char *str, int *j, int i);
char	*invalid_env(char **str, char **env_name);
char	*do_expand(t_env **lst_env, char *str, int index, char **split);
char	*get_expanded(char *new_str, t_env *env, char *str, int index);

char	*remove_quotes(char *str, char **split);

#endif
