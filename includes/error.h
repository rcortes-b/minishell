#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"

//void	free_words();
void	handle_error();
void	free_mem(char **split);
void	handle_split_error(char **split);

#endif