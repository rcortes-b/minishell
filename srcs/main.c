#include "../includes/parse.h"
#include "../includes/minishell.h"
#include "../includes/checker.h"
#include "../includes/expander.h"
#include "../includes/error.h"
#include "../includes/builtins.h"
#include "../includes/exec.h"
//char **spl = ft_split("ls -a > cat -b > mid -c > out -d", " \t");



static void	parse_main(t_word *words, char *line, t_env **env)
{
	//t_env		*env;
	t_operators	data;
	char		**split;

	init_data(&data);
	printf("Line: %s\n", line);
	printf("\n");
	split = ft_split(line, " \t", &data); //Error Handled *** Not Tested
	for (int i = 0; split[i]; i++)
		printf("Split %d: %s\n", i + 1, split[i]);
	free(line);
	//parse_environment(&env, envp); //Error Handled *** Not Tested
	//empty_export(&env);
	check_tokens(split, &data, env); //Error Handled *** Not Tested
	split = expand_cli(split, env); //Error Handled *** Not Tested
	printf("\n");
	for (int i = 0; split[i]; i++)
		printf("Expanded Split %d: %s\n", i + 1, split[i]);
	order_split(split, &data); //MODIFY THIS *** EL PRIMER COMANDO PUEDE SER INFILE
	printf("\n");
	for (int i = 0; split[i]; i++)
		printf("Expanded && Sorted Split %d: %s\n", i + 1, split[i]);
	categorize(split, &words, &data, env); //Error Handled *** Not Tested
	tokenization(&words, &data); //Error Handled *** Not Tested
	execution(&words, &data, env);
	/*printf("\n");
	t_word *aux = words;
	while (aux)
	{
		int	i = -1;
		printf("com: %s\n", aux->com);
		if (aux->flags) {
		printf("flags:\n");
		while (aux->flags[++i])
			printf("  - %s\n", aux->flags[i]); }
		printf("Token: %d\n", aux->token);
		aux = aux->next;
		printf("\n");
	}*/
	//free_env_mem(&env);
	free_struct_nodes(&words);
	free(split); /* Solo se libera el array general del split, ya que las otras direcciones estan en words */
}

int main(int argc, char **argv, char **envp)
{
	t_word	*words;
	t_env	*env;
	char *line;

	words = NULL;
	argc = 0;
	argv = NULL;
	g_errstatus = 0;
	parse_environment(&env, envp);
	while (1)
	{
		do_signal();
		signal(SIGTSTP, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		if (!line[0])
			continue ;
		add_history(line);
		parse_main(words, line, &env);
	}
}
