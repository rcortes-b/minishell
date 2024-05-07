/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvallhon <mvallhon@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:50:42 by mvallhon          #+#    #+#             */
/*   Updated: 2024/04/02 17:58:51 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"
#include "../../includes/error.h"

t_env	*ft_newenv(void)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->value = NULL;
	new->key = NULL;
	return (new);
}

void	ft_envadd_back(t_env **env_lst, t_env *new_env)
{
	t_env	*aux;

	if (!new_env)
		return ;
	if (*env_lst == NULL)
	{
		*env_lst = new_env;
		return ;
	}
	aux = *env_lst;
	while (aux->next != NULL)
		aux = aux->next;
	aux->next = new_env;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	**renew_env(t_env **env)
{
	char	**new_env;
	char	*new_aux;
	t_env	*env_aux;
	int		i;

	env_aux = *env;
	new_env = ft_calloc(ft_envsize(env_aux) + 1, sizeof(char *));
	i = 0;
	if (!new_env)
		return (NULL);
	while (env_aux)
	{
		if(!env_aux->only_exp)
		{
			new_aux = ft_strdup(env_aux->key);
			if (!new_aux)
				handle_error();
			new_aux = ft_strjoin_v3(new_aux, "=");
			if (!new_aux)
				handle_error();
			if (env_aux->value)
			{
				new_aux = ft_strjoin_v3(new_aux, env_aux->value);
				if (!new_aux)
					handle_error();
			}
			new_env[i++] = new_aux;
		}
		env_aux = env_aux->next;
	}
	return (new_env);
}