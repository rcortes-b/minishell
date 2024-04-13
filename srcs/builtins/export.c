#include "../../includes/exec.h"
#include "../../includes/builtins.h"
#include "../../includes/error.h"

static char	*new_str(char *value, int size)
{
	char	*new_str;
	int		i;

	new_str = (char *)malloc(sizeof(char) * size + 1);
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < size)
		new_str[i] = value[i];
	new_str[i] = '\0';
	return (new_str);
}

/* a partir de la key todo es valido 
1- comrobar si hay igual para el only export, si es onlyexp 0 funcion de checker

*/

static void	add_export(t_env **env, char *value)
{
	t_env	*new_env;
	int	only_export;
	int	i;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (!new_env)
		printf("Error.\n");
	i = -1;
	only_export = 1;
	while (value[++i])
	{
		if (!only_export && !new_env->value)
			new_env->value = new_str(&value[i], ft_strlen(&value[i]));
		if (value[i] == '=')
		{
			new_env->key = new_str(value, i);
			only_export = 0;
		}
	}
	new_env->only_exp = only_export;
	new_env->next = NULL;
	ft_envadd_back(env, new_env);
}

void	do_export(t_exe **vars)
{
	int	i;

	i = 0;
	if (!(*(*vars)->lst)->flags[1])
		empty_export((*vars)->env);
	else
	{
		while ((*(*vars)->lst)->flags[++i])
			add_export((*vars)->env, (*(*vars)->lst)->flags[i]);
	}
}