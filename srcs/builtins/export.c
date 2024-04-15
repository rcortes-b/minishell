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

static void	new_var(t_env **env, char *value, int is_onlyexp, int is_append)
{
	t_env	*new;
	int		i;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		printf("Error malloc.\n");
	new->only_exp = is_onlyexp;
	new->next = NULL;
	i = 0;
	while (value[i] && value[i] != '=' && value[i] != '+')
		i++;
	new->key = ft_substr(value, 0, i);
	printf("Value: %s  NEW KEY: %s  I: %d\n", value, new->key, i);
	if (!new->key)
		printf("Malloc error en substr.\n");
	if (is_onlyexp)
	{
		new->value = malloc(1);
		new->value[0]= '\0';
	}
	else
	{
		if (is_append)
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
	//while (value[i - 1] != '=')
	while (value[i] != '=' && value[i] != '+')
		i++;
	aux = *env;
	while (ft_strncmp(aux->key, value, i) != 0)
		aux = aux->next;
	if (aux->only_exp)
		aux->only_exp = is_onlyexp;
	if (is_append)
	{
		aux->value = ft_strjoin(aux->value, &value[i + 2]);
		if (!aux->value)
			printf("strjoin error.\n");
	}
	else
	{
		//if (aux->value)
		//	free(aux->value);
		printf("VALUEEEE %p\n", aux->value);
		//lolazo(&aux, &value[i]);
		aux->value = ft_strdup(&value[i + 1]);
		if (!aux->value)
			printf("strdup error.\n");
		printf("AUCS VALIU: %p\n", aux->value);
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
	is_append = 0;
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
		new_var(env, value, is_onlyexp, is_append);
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