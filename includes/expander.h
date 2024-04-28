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
	int		quote_amount;
	int		*del_index;
	int		s_counter;
	int		*d_del_index;
	int		d_counter;
	int		*expanded_quote;
	int		skip_counter;
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
int		check_if_ambiguos(t_env **env, char **split, int index);
char	*set_do_expand(int *j, int *index, char *str, int *is_quote);
void	is_not_split(t_exp *exp);

//Split for Expansor
char	**expander_split(char const *s, char c);
void	resize_index(t_exp *exp, char *str, int *index);

//Remove Quotes
char	*prep_quotes(char *str, int index, t_exp *exp);
int		is_quoted_operator(char *str);
char	*aux_check_operator(char **new_split);
void	prep_quotes_aux(char *str, char *lead,
			int *lead_counter, int *index);
int		expansion_supreme(t_exp *exp, int *i, t_env **lst_env, char lead);
char	*expand_home(t_env **env, char *str);
void	update_del_index(t_exp *exp, int i, int **tab, char lead);
char	*delete_remain_quotes(t_exp *exp, int *tab, char lead, int limit_counter);
int		check_if_delquote(char *str, int i, char lead, t_exp *exp);
void	update_index_to_del(t_exp *exp);
void	skip_index_expquote(t_exp *exp, int index, t_env *env);
int		skip_quote(int i, t_exp *exp);
int		is_ddel_quote(char *str, int i, t_exp *exp);
int		is_dquote(char *str, int i, t_exp *exp);

char	*rm_quotes_expand(t_exp *exp, char *str, int index);

#endif
