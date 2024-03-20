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


int		check_if_operator(t_operators *data, char c);
void	free_mem(char **split);
void	init_data(t_operators *data);
int		is_operator(char *line, int index, t_operators *data);
void	get_word_quote(char **word, char *line, int *index, char c);
int		count_words(char *line, const char *set, t_operators *data);

#endif