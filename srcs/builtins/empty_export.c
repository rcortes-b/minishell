#include "../../includes/parse.h"
#include "../../includes/builtins.h"
#include "../../includes/error.h"

static void	print_export(t_env **env)
{
	t_env	*aux;

	aux = *env;
	while (aux)
	{
		if (ft_strcmp(aux->key, "_") != 0)
		{
			if (aux->only_exp)
				printf("declare -x %s\n", aux->key);
			else
				printf("declare -x %s=\"%s\"\n", aux->key, aux->value);
		}
		aux = aux->next;
	}
}

static void	ft_swap_env(t_env **aux, t_env **tmp)
{
	char	*str_aux;
	int		temp;

	str_aux = (*aux)->key;
	(*aux)->key = (*tmp)->key;
	(*tmp)->key = str_aux;

	str_aux = (*aux)->value;
	(*aux)->value = (*tmp)->value;
	(*tmp)->value = str_aux;

	temp = (*aux)->only_exp;
	(*aux)->only_exp = (*tmp)->only_exp;
	(*tmp)->only_exp = temp;
}

static void	sort_list(t_env **env)
{
	t_env	*aux;
	t_env	*tmp;
	int		i;

	i = 0;
	aux = *env;
	while (aux)
	{
		tmp = aux->next;
		while (tmp)
		{
			if (aux->key[0] > tmp->key[0])
				ft_swap_env(&aux, &tmp);
			else if (aux->key[0] == tmp->key[0])
			{
				i = 0;
				while (aux->key[i] == tmp->key[i])
					i++;
				if (aux->key[i] > tmp->key[i])
					ft_swap_env(&aux, &tmp);
			}
			tmp = tmp->next;
		}
		aux = aux->next;
	}
}

void	empty_export(t_env **lst_env)
{
	t_env	*exp;
	t_env	*aux;
	t_env	*new;
	int		is_oldpwd;

	exp = *lst_env;
	aux = *lst_env;
	is_oldpwd = 0;
	while (aux)
	{
		if (ft_strcmp(aux->key, "OLDPWD") == 0)
			is_oldpwd = 1;
		aux = aux->next;
	}
	if (!is_oldpwd)
	{
		new = ft_newenv();
		new->key = ft_strdup("OLDPWD");
		new->value = NULL;
		new->only_exp = 1;
		ft_envadd_back(&exp, new);
	}
	sort_list(&exp); /* Se puede crear una lista nueva para que no haga sorting del env y solo del export :) */
	print_export(&exp);
}
