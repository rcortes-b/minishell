#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

typedef struct s_operator
{
	char 	pipe;
	char	squote;
	char	dquote;
	char 	reinput;
	char 	reoutput;
}	t_operators;

typedef struct s_word
{
	char			*com;
	char			**flags;
	int				token;
	struct s_word	*next;
}	t_word;

//ESTO ES SPLIT
int		check_if_operator(t_operators *data, char c);
void	free_mem(char **split);
void	init_data(t_operators *data);
int		is_operator(char *line, int index, t_operators *data);
void	get_word_quote(char **word, char *line, int *index, char c);
int		count_words(char *line, const char *set, t_operators *data);
char	**ft_split(char *line, const char *set, t_operators *data);

//ESTO ES ORDER
int		is_symbol(t_operators *data, char c);
void	order_split(char **split, t_operators *data);

//ESTO ES CATEGORIZE
void	categorize(char **words, t_word **lst);
t_word	*new_word(char **words, int start, int end);
void	wordadd_back(t_word **words, t_word *new_word);

#endif
