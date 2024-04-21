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
	split = ft_split(line, " \t", &data);
	free(line);
	if (!split)
	{
		free_env_mem(env);
		handle_error();
	}
	check_tokens(split, &data, env);
	split = lets_expand(env, split);
	if (!split)
		handle_env_error(env, split);
	order_split(split, &data);
	categorize(split, &words, env);
	free(split);
	tokenization(&words, &data);
	//Hasta aqui esta checkeao y ta bien (BORRAR ESTE COMMENT 20/04)
	if (!execution(&words, &data, env))
		exit(1);
	free_struct_nodes(&words);
	//free_env_mem(env);
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
		{
			free(line);
			continue ;
		}
		add_history(line);
		do_line(words, line, &env);
	}
	return (1);
}
