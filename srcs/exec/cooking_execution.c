#include "../../includes/expander.h"
#include "../../includes/parse.h"
#include "../../includes/error.h"

static char	**append_bar(char **split)
{
	char	**path;
	int		j;

	j = 0;
	while (split[j])
		j++;
	path = malloc(sizeof(char *) * (j + 1));
	if (!path)
		do_error(split, "utils.c Line 48: Malloc Error", -2);
	j = -1;
	while (split[++j])
	{
		path[j] = ft_strjoin(split[j], "/");
		if (!path[j])
		{
			do_error(path, NULL, 0);
			do_error(split, "utils.c Line 56: Malloc Error", -2);
		}
		free(split[j]);
	}
	free(split);
	path[j] = NULL;
	return (path);
}

static char	**parse_path(t_env **my_env)
{
	t_env	*my_paths;
	char	**paths;
	int		i;

	my_paths = get_env(my_env, "PATH");
	i = 0;
	while (my_paths->value[i] != '/')
		i++;
	paths = ft_esplit(my_paths->value[i], ':');
	if (!paths)
	{
		ft_putendl_fd("utils.c Line 83: Malloc Error", 2);
		exit(EXIT_FAILURE);
	}
	paths = append_bar(paths);
}

int	cooking_execution(t_word **lst, t_env **my_env)
{
	char **paths;
	t_word	*aux;

	aux = *lst;
	paths = parse_path(my_env);
	if (!paths)
		return (0); //error handling su puta madre
	while (aux)
	{
		if (aux->token != 1)
			ejecutar_cosas();
		aux = aux->next;
	}
}