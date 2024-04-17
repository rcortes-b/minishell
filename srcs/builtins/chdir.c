#include "../../includes/builtins.h"
#include "../../includes/parse.h"
//#include "../../includes/exec.h"

/*
Comprobar si es relativo o absoluto el path DONE
Comprobar si existe y puedes acceder
Cambiar el directory
Actualizar el pwd y el oldpwd

------Check de que solo si la siguiente structura es NULL y te han pasado bien el input---- Solo un path despues del ch y nada mas , aux.next == NULL------
*/

char	*parse_home(t_env *home, char **path)
{
	char	*new_path;

	new_path = ft_strdup(home->value);
	if(!new_path)
		printf("error poniendo la primera parte");
	new_path = ft_strjoin(new_path, &(*path)[1]);
	if (!new_path)
		printf("error juntando todo el path modified.\n");
	free(*path);
	return (new_path);
}

static char	*is_absolute(t_exe *vars, char *path, int *is_relative)
{
	t_env	*aux;
	int		home_size;

	aux = get_env(vars->env, "HOME");
	home_size = ft_strlen(aux->value);
	if (path[0] == '~' && (path[1] == '/' || !path[1]))
	{
		path = parse_home(aux, &path);
		*is_relative = 0;
	}
	else if (ft_strncmp(aux->value, path, home_size) == 0 && (path[home_size] == '/' || !path[home_size]))
		*is_relative = 0;
	return (path);
}


static void	update_directory(t_env **env, char **old_pwd)
{
	t_env	*new = NULL;
	t_env	*aux;
	t_env	*old;
	char	*tmp_pwd;

	aux = get_env(env, "PWD");
	tmp_pwd = ft_strdup(aux->value);
	if (!tmp_pwd)
		printf("strdup error.\n");
	free(aux->value);
	aux->value = getcwd(NULL, 0);
	if (!aux->value)
	{
		aux->value = ft_strdup(tmp_pwd);
		if (!aux->value)
			printf("strdup error.\n");
	}
	free(tmp_pwd);
	old = get_env(env, "OLDPWD");
	if (!old)
	{
		new = ft_newenv();
		new->key = ft_strdup("OLDPWD");
		new->value = *old_pwd;
		ft_envadd_back(env, new);
		new->only_exp = 0;
	}
	else
	{
		if (old->value)
			free(old->value);
		old->value = *old_pwd;
		old->only_exp = 0;
	}
}

void	change_directory(t_exe *vars)
{
	t_env	*aux;
	char	*old_pwd;
	int		is_relative;

	is_relative = 1;
	aux = get_env(vars->env, "PWD");
	old_pwd = ft_strdup(aux->value);
	if (!old_pwd)
		printf("fallo de strdup.\n");
	if ((*vars->lst)->flags[2])
		printf("Error porque solo puede recibir un path rel or abs.\n");
	(*vars->lst)->flags[1] = is_absolute(vars, (*vars->lst)->flags[1], &is_relative);
	if (access((*vars->lst)->flags[1], X_OK) != 0)
		printf("no such file or dir.\n");
	else
	{
		if (chdir((*vars->lst)->flags[1]) == 0)
		{
			update_directory(vars->env, &old_pwd);
			printf("sa cambiao.\n"); //getcwd, update pwd and update oldpwd
		}
		else
		{
			free(old_pwd);
			printf("no sa cambiao.\n"); //no se hace nada
		}
	}
	char buff[100];
	getcwd(buff, 100);
	//else
	printf("PATH: %s\n", (*vars->lst)->flags[1]);
	printf("NEW PATH: %s\n", buff);
	printf("Is Relative: %d\n", is_relative);
}