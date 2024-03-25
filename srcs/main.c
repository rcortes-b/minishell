#include "../includes/parse.h"
#include "../includes/minishell.h"
#include "../includes/checker.h"

//char **spl = ft_split("ls -a > cat -b > mid -c > out -d", " \t");

static void	parse_main(t_word *words, char *line, char **envp)
{
	t_list		*env;
	t_operators	data;
	char		**split;

	env = NULL;
	init_data(&data);
	printf("Line: %s\n", line);
	printf("\n");
	split = ft_split(line, " \t", &data);
	check_tokens(split, &data);
	order_split(split, &data); //MODIFY THIS *** EL PRIMER COMANDO PUEDE SER INFILE
	parse_environment(&env, envp);
	categorize(split, &words, &data);
	tokenization(&words, &data);
	while (words)
	{
		int	i = -1;
		printf("com: %s\n", words->com);
		if (words->flags) {
		printf("flags:\n");
		while (words->flags[++i])
			printf("  - %s\n", words->flags[i]); }
		printf("Token: %d\n", words->token);
		words = words->next;
		printf("\n");
	}
}

int main(int argc, char **argv, char **envp)
{
	t_word	*words;
	char *line;

	words = NULL;
	argc = 0;
	argv = NULL;
	line = readline("minishell> ");
	parse_main(words, line, envp);
}
