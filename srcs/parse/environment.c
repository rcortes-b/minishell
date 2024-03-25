#include "../../includes/parse.h"

char	*get_env(t_list **lst, char *key)
{
	t_list	*aux;

	aux = *lst;
	while (aux && ft_strncmp(aux, key, ft_strlen(key) != 0))
		aux = aux->next;
	if (!aux)
		return (NULL);
	return (aux->content);
}

void	parse_environment(t_list **lst, char **envp)
{
	t_list	*aux;
	int		i;

	*lst = NULL;
	i = -1;
	while (envp[++i])
	{
		aux = ft_lstnew(envp[i]);
		ft_lstadd_back(lst, aux);
	}
}
