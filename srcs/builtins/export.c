#include "../../includes/exec.h"
#include "../../includes/builtins.h"
#include "../../includes/error.h"


// a partir de la key todo es valido 
//1- comrobar si hay igual para el only export, si es onlyexp 0 funcion de checker

static int	var_exists(t_env *env, char *value, int size)
{
	t_env	*aux;

	aux = env;
	while (aux)
	{
		if (ft_strncmp(aux->key, value, size) == 0)
			return (1);
		aux = aux->next;
	}
	return (0);
}

static void	new_var(t_env **env, char *value, int is_onlyexp)
{
	t_env	*new;
	int		i;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		printf("Error malloc.\n");
	new->only_exp = is_onlyexp;
	new->next = NULL;
	i = 0;
	while (value[i] && (value[i] != '=' || (value[i] != '+' && value[i + 1] == '=')))
		i++;
	new->key = ft_substr(value, 0, i);
	if (!new->key)
		printf("Malloc error en substr.\n");
	if (is_onlyexp)
		new->value = NULL;
	else
	{
		if (value[i] == '+')
			i += 2;
		else
			i++;
		new->value = ft_strdup(&value[i]);
	}
	ft_envadd_back(env, new);
}

static void	update_var(t_env **env, char *value, int is_append, int is_onlyexp)
{
	t_env	*aux;
	int		i;

	if (is_onlyexp)
		return ;
	i = 0;
	while (value[i - 1] != '=')
		i++;
	aux = *env;
	while (ft_strncmp(aux->key, value, i))
		aux = aux->next;
	if (is_append)
	{
		if (!ft_strjoin(aux->value, &value[i]))
			printf("strjoin error.\n");
	}
	else
	{
		free(aux->value);
		aux->value = ft_strdup(&value[i]);
		if (!aux->value)
			printf("strdup error.\n");
	}
}

static void	add_export(t_env **env, char *value)
{
	int	is_onlyexp;
	int	is_append;
	int	is_new;
	int	i;

	i = -1;
	is_new = 1;
	is_onlyexp = 0;
	while (value[++i] && (value[i] != '=' || (value[i] != '+' && value[i + 1] == '=')))
	{
		if (value[i] == '+' && value[i + 1] == '=')
		{
			is_append = 1;
			break ;
		}
	}
	if (var_exists(*env, value, i))
		is_new = 0;
	if (!value[i])
		is_onlyexp = 1;
	if (is_new)
		new_var(env, value, is_onlyexp);
	else
		update_var(env, value, is_append, is_onlyexp);
}

void	do_export(t_word *lst, t_exe **vars)
{
	int	i;

	i = 0;
	if (!lst->flags[1])
		empty_export((*vars)->env);
	else
	{
		while (lst->flags[++i])
		{
			if (lst->flags[i][0] == '_' && lst->flags[i][1] == '=')
				return ;
			if (!key_is_valid(lst->flags[i]))
				printf("Key is not valid.!\n");
			else
				add_export((*vars)->env, lst->flags[i]);
		}
	}
}