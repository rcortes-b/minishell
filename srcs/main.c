#include "../includes/parse.h"
#include "../includes/minishell.h"
#include "../includes/checker.h"
#include "../includes/expander.h"
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
	for (int i = 0; split[i]; i++)
		printf("Split %d: %s\n", i + 1, split[i]);
	check_tokens(split, &data);
	order_split(split, &data); //MODIFY THIS *** EL PRIMER COMANDO PUEDE SER INFILE
	parse_environment(&env, envp);
	//char *pepe = get_env(&env, "PATHI");
	//printf("Env got: %s\n", pepe);
	categorize(split, &words, &data);
	tokenization(&words, &data);
	expand_cli(&words, &env);
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
