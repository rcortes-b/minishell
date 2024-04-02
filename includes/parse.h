/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:16:58 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/02 17:58:45 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

//ESTO ES SPLIT
void	copy_quotes(char *word, char *line, int *i, int *index);
void	iterate_quote(char *line, int *index, char c, int *size);
int		do_operator(char *line, int *index, t_operators *data, int *size);
int		split_word_symbol(char **word, char *line,
			int *index, t_operators *data);
char	**ft_split(char *line, const char *set, t_operators *data);

//ESTO ES ORDER FLAGS && PARSE UTILS
void	init_data(t_operators *data);
int		is_symbol(t_operators *data, char c);
void	order_split(char **split, t_operators *data);

//ESTO ES CATEGORIZE && TOKENIZATION
void	categorize(char **words, t_word **lst, t_operators *data);
void	tokenization(t_word **lst, t_operators *data);

//ESTO ES ENVIRONMENT
typedef struct s_env
{
	char			*key;
	char			*value;
	int				only_exp;
	struct s_env	*next;
}					t_env;

t_env	*ft_newenv(char *env);
void	ft_envadd_back(t_env **env_lst, t_env *new_env);
void	parse_enviroment(t_env **env_lst, char **envp);
int		ft_strcmp(char *s1, char *s2);
char	*get_env(t_env **env_lst, char *get_key);
//ENVIROMENT ANTIGUO PELIGRO!!
//void	parse_environment(t_list **lst, char **envp);
//char	*get_env(t_list **lst, char *key);

#endif
