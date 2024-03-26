#include "../../includes/error.h"

void	handle_error(void)
{
	perror("Error");
	exit(errno);
}

void	free_mem(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

void	handle_split_error(char **split)
{
	free_mem(split);
	handle_error();
}