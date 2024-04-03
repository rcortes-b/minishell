/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:23:16 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/02 18:07:39 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/parse.h"

static char	*get_expanded(char *new_str, t_env *env, char *str, int index)
{
	int	i;
	int	j;
	int	k;
	int	key_len;

	i = -1;
	while (++i < index)
		new_str[i] = str[i];
	j = 0;
	key_len = ft_strlen(env->key);
	k = i + key_len + 1;
	while (env->value[j])
		new_str[i++] = env->value[j++];
	j = 1;
	while (str[k])
		new_str[i++] = str[k++];
	new_str[i] = '\0';
	return (new_str);
}

static char	*do_expand(t_env **lst_env, char *str, int index)
{
	char	*env_name;
	t_env	*env;
	char	*new_str;
	int		i;
	int		j;

	i = index + 1;
	j = 0;
	while (str[i])
	{
		while (str[i + j] && str[i + j] != '$'
			&& str[i + j] != '"' && str[i + j] != '\'' && str[i + j] != ' ')
			j++;
		env_name = ft_substr(str, i, j);
		if (!env_name)
			return (NULL);
		env = get_env(lst_env, env_name);
		if (!env)
			return (NULL);
		new_str = malloc(ft_strlen(str) + ft_strlen(env->value) - ft_strlen(env->key) - 1);
		new_str = get_expanded(new_str, env, str, index);
		free(str);
		return (new_str);
	}
	return (NULL);
}

static void	check_if_expand(t_env **lst_env, char **str)
{
	int		i;
	char	lead;
	int		second;

	second = 0;
	lead = 'x';
	i = -1;
	while (str[0][++i])
	{
		if (!second && (str[0][i] == '"' || str[0][i] == '\''))
		{
			lead = str[0][i];
			second = 1;
		}
		else if (second && str[0][i] == lead)
		{
			lead = 'x';
			second = 0;
		}
		if (str[0][i] == '$' && lead != '\'' )
		{
			*str = do_expand(lst_env, *str, i);
			
			second = 0;
			i = -1;
			//eprintf("Str: %s\n", *str);
		}
	}
}

void	expand_cli(char **words, t_env **lst_env)
{
	int	i;

	i = -1;
	while (words[++i])
		check_if_expand(lst_env, &words[i]);
}

/*static char	*remove_quotes(char *str)
{
	char	lead;
	char	*new_comm;
	int		i;
	int		lead_counter;

	lead = 'x';
	lead_counter = 0;
	i = -1;
	while (str[++i])
	{
		while (str[i] && str[i] != '"' && str[i] != '\'')
			i++;
		if (str[i] == '\'' || str[i] == '"')
		{
			lead = str[i++];
			lead_counter++;
		}
		while (str[i] && str[i] != lead)
			i++;
	}
	new_comm = (char *)malloc(ft_strlen(str) - (lead_counter * 2) + 1);
	if (!new_comm)
		printf("loll error\n");
	return (del_quotes(str, new_comm));
}

char	*del_quotes(char *str, char *new_str)
{
	char	lead;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			lead = str[i++];
			while (str[i] != lead)
				new_str[j++] = str[i++];
			i++;
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free(str);
	str = NULL;
	return (new_str);
}*/
