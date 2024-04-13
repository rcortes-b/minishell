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
	int		i;

	aux = *env;
	while (aux)
	{
		i = 0;
		while (values[++i])
		{
			if (ft_strcmp(aux->next->key, values[i]) == 0)
			{
				update_env(&aux, &aux->next);
				break ;
			}
		}
		aux = aux->next;
	}
}
