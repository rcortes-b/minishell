/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:22:55 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/02 17:58:49 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"
#include "../../includes/error.h"

void	exit_env(t_env **env)
{
	free_env_mem(env);
	exit(1);
}

void	aux_init_env(t_env **env, t_env *aux)
{
	aux = ft_newenv();
	if (!aux)
		exit_env(env);
	ft_envadd_back(env, aux);
	aux->key = ft_strdup("PATH");
	if (!aux->key)
		exit_env(env);
	aux->value = ft_strdup("/Users/rcortes-/.brew/bin:/Users/rcortes-/goinfre/.\
	brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Applications/VMware F\
	usion.app/Contents/Public:/usr/local/go/bin:/usr/local/munki:/Users/rcortes-\
	/.brew/bin:/Users/rcortes-/goinfre/.brew/bin");
	if (!aux->value)
		exit_env(env);
	aux->only_exp = 1;
	aux = ft_newenv();
	if (!aux)
		exit_env(env);
	ft_envadd_back(env, aux);
	aux->key = ft_strdup("HOME");
	if (!aux->key)
		exit_env(env);
	aux->value = ft_strdup("/Users/rcortes-");
	if (!aux->value)
		exit_env(env);
	aux->only_exp = 1;
}

void	init_env(t_env **env, char **envp)
{
	t_env	*aux;

	if (envp && *envp)
		return ;
	aux = ft_newenv();
	if (!aux)
		exit (1);
	ft_envadd_back(env, aux);
	aux->key = ft_strdup("PWD");
	if (!aux->key)
		exit_env(env);
	aux->value = getcwd(NULL, 0);
	aux->only_exp = 0;
	aux = ft_newenv();
	if (!aux)
		exit_env(env);
	ft_envadd_back(env, aux);
	aux->key = ft_strdup("SHLVL");
	if (!aux->key)
		exit_env(env);
	aux->value = ft_strdup("1");
	if (!aux->value)
		exit_env(env);
	aux->only_exp = 0;
	aux_init_env(env, aux);
}

t_env	*get_env(t_env **env_lst, char *get_key)
{
	t_env	*aux;

	aux = *env_lst;
	while (aux)
	{
		if (ft_strcmp(get_key, aux->key) == 0)
			return (aux);
		aux = aux->next;
	}
	return (NULL);
}

t_env	*parse_environment(t_env **env_lst, char **envp)
{
	t_env	*aux;
	int		i;
	int		j;

	*env_lst = NULL;
	i = -1;
	while (envp[++i])
	{
		j = 0;
		aux = ft_newenv();
		if (!aux)
			return (free_env_mem(env_lst), NULL);
		while (envp[i][j] != '=')
			j++;
		aux->key = ft_substr(envp[i], 0, j);
		if (!aux->key)
			return (free_env_mem(env_lst), free(aux), NULL);
		j++;
		aux->value = ft_substr(envp[i], j, ft_strlen(envp[i]));
		if (!aux->value)
			return (free_env_mem(env_lst), free(aux), free(aux->key), NULL);
		aux->only_exp = 0;
		ft_envadd_back(env_lst, aux);
	}
	return (*env_lst);
}
