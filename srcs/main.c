/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 12:05:19 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/21 12:05:20 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	check_line(char *line, t_env **env)
{
	if (!line)
	{
		free_env_mem(env);
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	if (!line[0])
	{
		free(line);
		return (0);
	}
	return (1);
}

static void	aux_do_line(t_word *words, t_operators *data,
		t_env **env, char **split)
{
	order_split(split, data);
	if (!categorize(split, &words))
		return ;
	free(split);
	tokenization(&words, data);
	//Hasta aqui esta checkeao y ta bien (BORRAR ESTE COMMENT 21/04)
	execution(&words, data, env);
	free_struct_nodes(&words);
}

static void	do_line(t_word *words, char *line, t_env **env, char **og_env)
{
	t_operators	data;
	char		**split;

	init_data(&data, og_env);
	split = ft_split(line, " \t", &data);
	free(line);
	if (!split)
	{
		handle_error();
		return ;
	}
	if (!check_tokens(split, &data))
		return ;
	split = lets_expand(env, split);
	if (!split)
	{
		handle_error();
		return ;
	}
	aux_do_line(words, &data, env, split);
}

int	main(int argc, char **argv, char **envp)
{
	t_word	*words;
	t_env	*env;
	char	*line;

	check_args(argc, argv);
	words = NULL;
	env = NULL;
	g_errstatus = 0;
	while (1)
	{
		if (!env)
		{
			if (!parse_environment(&env, envp))
				handle_error();
		}
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		line = readline("minishell> ");
		if (!check_line(line, &env))
			continue ;
		add_history(line);
		do_line(words, line, &env, envp);
	}
	return (0);
}
