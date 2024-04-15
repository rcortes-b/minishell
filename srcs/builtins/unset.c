#include "../../includes/parse.h"
#include "../../includes/builtins.h"
#include "../../includes/error.h"

void	update_env(t_env **aux, t_env **del_node)
{
	t_env	*tmp;

	tmp = (*del_node)->next;
	free((*del_node)->key);
	free((*del_node)->value);
	free(*del_node);
	(*aux)->next = tmp;
}

void	unset_env(t_env **env, char **values)
{
	t_env	*aux;
	int		is_last;
	int		i;

	aux = *env;
	is_last = 0;
	while (aux->next)
	{
		i = 0;
		while (values[++i])
		{
			if (ft_strcmp(aux->next->key, values[i]) == 0)
			{
					printf("LOL.\n");
				update_env(&aux, &aux->next);
				is_last = 1;
				break ;
			}
		}
		if (is_last)
			is_last = 0;
		else
			aux = aux->next;
	}
}
