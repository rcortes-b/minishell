#include "../includes/parse.h"
#include "../includes/minishell.h"
#include "../includes/checker.h"
#include "../includes/expander.h"
#include "../includes/error.h"
//char **spl = ft_split("ls -a > cat -b > mid -c > out -d", " \t");

static void	parse_main(t_word *words, char *line, char **envp)
{
	t_env		*env;
	t_operators	data;
	char		**split;

	init_data(&data);
	parse_environment(&env, envp);
	printf("Line: %s\n", line);
	printf("\n");
	split = ft_split(line, " \t", &data);
	for (int i = 0; split[i]; i++)
		printf("Split %d: %s\n", i + 1, split[i]);
	check_tokens(split, &data);
	expand_cli(split, &env);
	printf("\n");
	for (int i = 0; split[i]; i++)
		printf("Expanded Split %d: %s\n", i + 1, split[i]);
	order_split(split, &data); //MODIFY THIS *** EL PRIMER COMANDO PUEDE SER INFILE
	printf("\n");
	for (int i = 0; split[i]; i++)
		printf("Expanded && Sorted Split %d: %s\n", i + 1, split[i]);
	/* HASTA AQUI ESTA DE PUTA MADRE QUE LOCURA */
	//char *pepe = get_env(&env, "PATHI");
	//printf("Env got: %s\n", pepe);
	categorize(split, &words, &data);
	tokenization(&words, &data);
	printf("\n");
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
