/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:05:51 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/19 16:05:52 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*int main(int argc, char **argv, char **envp)
{
	char	*cli;
	cli = readline("minishell> ");
	argc = 0;
	argv = NULL;
	char **spl = ft_split("ls", ' ');
	for (int i = 0; envp[i]; i++)
		printf("%s\n", envp[i]);
	printf("\n\n");
	int j = -1;
	while (++j < 1)
	{
		pid_t pid = fork();
		if (pid == 0)
			execve("/bin/ls", spl, NULL);
		chdir("..");
		cli = readline("minishell> ");
		for (int i = 0; envp[i]; i++)
			printf("%s\n", envp[i]);
		execve("/bin/ls", spl, NULL);
	}
	printf("You completed minishell!\n");
}*/

int main(void)
{
	char *line = getenv("C_INCLUDE_PATH");
	printf("%s\n", line);
}