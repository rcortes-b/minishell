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

typedef struct s_exp
{
	char	**og_split;
	char	**new_split;
	char	*expanded_str;
	int		index;
	int		new_index;
	int		is_first;
	int		is_split;
}	t_exp;

//Utils
char	*invalid_env(char *new_str, char *env_name, char *str, int index);
void	iterate_expand(char *str, int *j, int i);
void	set_expand_values(char *lead, int *quote, char c, int *index);
int		is_expanded(char const *s1, char const *s2);
int		aux_create_split(t_exp *exp, char **def_split, int counter, int j);
int		expander_aux(t_exp *exp, t_env **lst_env, char *str, char *lead);

//Expand
int		modify_split(t_exp *exp, char *str);
char	*get_expanded(char *new_str, t_env *env, char *str, int index);
char	**lets_expand(t_env **lst_env, char **split);
char	*do_expand(t_env **lst_env, char *str, int index, t_exp *exp);

//Split for Expansor
char	**expander_split(char const *s, char c);

//Remove Quotes
int		remove_quotes(char **new_split);

char	*expand_home(t_env **env, char *str);

#endif
