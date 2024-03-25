#include "../../includes/parse.h"

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