#include "../../includes/exec.h"
#include "../../includes/builtins.h"
#include "../../includes/error.h"

void	print_pwd(t_env *env)
{
	t_env	*aux;

	aux = env;
	while (aux)
	{
		if (ft_strcmp(aux->key, "PWD") == 0)
			printf("%s\n", aux->value);
		aux = aux->next;
	}
}
