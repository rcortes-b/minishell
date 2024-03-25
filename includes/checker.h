#ifndef CHECKER_H
# define CHECKER_H

#include "minishell.h"
#include "parse.h"

//void	check_tokens(t_word **lst, t_operators *data);
void	check_tokens(char **words, t_operators *data);

#endif