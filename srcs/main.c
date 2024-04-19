#include "../includes/parse.h"
#include "../includes/minishell.h"
#include "../includes/checker.h"
#include "../includes/expander.h"
#include "../includes/error.h"
#include "../includes/builtins.h"
#include "../includes/exec.h"

static void	check_args(int argc, char **argv)
{
	if (argc > 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit(127);
	}
}

static void	do_line(t_word *words, char *line, t_env **env)
{
	t_operators	data;
	char		**split;

	init_data(&data);
	split = ft_split(line, " \t", &data); //HACER EL 'MAL CLOSE QUOTING' POR EL PERROR, etc 17/04
	free(line);
	if (!split)
	{
		free_env_mem(env);
		handle_error();
	}
	check_tokens(split, &data, env);
	split = lets_expand(env, split);
	//split = expand_cli(split, env); //Creo que esta mal 17/04 (Ingente cantidad de texto)
	//free_struct_nodes(&words);
	//free_env_mem(env);
	//exit(1);
	/*for (int l = 0; split[l]; l++)
		printf("Split After: %p\n", split[l]);
	for (int l = 0; split[l]; l++)
		printf("Split After: %s\n", split[l]);*/
	//printf("split main dir: %p\n", split);
	order_split(split, &data);
	categorize(split, &words, &data, env);
	free(split);
	tokenization(&words, &data);
	//Hasta aqui esta checkeao y ta bien (BORRAR ESTE COMMENT 17/04)
	execution(&words, &data, env);

	free_struct_nodes(&words);
	free_env_mem(env);
}

int main(int argc, char **argv, char **envp)
{
	t_word	*words;
	t_env	*env;
	char *line;

	check_args(argc, argv);
	words = NULL;
	g_errstatus = 0;
	if (!parse_environment(&env, envp))
		handle_error();
//	while (1)
	//{
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
		{
			free(line);
		//	continue ;
		}
		add_history(line);
		do_line(words, line, &env);
		return (1);
	//}
}
