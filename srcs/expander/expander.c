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
#include "../../includes/error.h"

static void	set_expand_values(char *lead, int *quote, char c, int *index)
{
	if (c == 'x')
		*quote = 0;
	else
		*quote = 1;
	*lead = c;
	if (index)
		*index = -1;
}

char	*get_expanded(char *new_str, t_env *env, char *str, int index)
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

char	*do_expand(t_env **lst_env, char *str, int index, char **split)
{
	char	*env_name;
	t_env	*env;
	char	*new_str;
	int		i;
	int		j;

	i = index + 1;
	j = 0;
	printf("strrrrrr: %s\n", str);
	while (str[i])
	{
		iterate_expand(str, &j, i);
		env_name = ft_substr(str, i, j);
		if (!env_name)
			return (NULL);
		env = get_env(lst_env, env_name);
		if (!env)
			return (free(env_name), free_mem(split), NULL);
		printf("QUEEE\n");
		new_str = malloc(ft_strlen(str) + ft_strlen(env->value)
				- ft_strlen(env->key) - 1);
		if (!new_str)
			return (free(env_name), free_mem(split), NULL);
		new_str = get_expanded(new_str, env, str, index);
		printf("%s\n", str);
		printf("new_str: %s\n", new_str);
		return (free(str), free(env_name), new_str);
	}
	return (NULL);
}

static char	*check_if_expand(t_env **lst_env, char **str, char ***split)
{
	int		i;
	char	lead;
	int		second;

	set_expand_values(&lead, &second, 'x', &i);
	while (str[0][++i])
	{
		if (!second && (str[0][i] == '"' || str[0][i] == '\''))
			set_expand_values(&lead, &second, str[0][i], NULL);
		else if (second && str[0][i] == lead)
			set_expand_values(&lead, &second, 'x', NULL);
		if (str[0][i] == '$' && lead != '\'')
		{
			*str = do_expand(lst_env, *str, i, *split);
			printf("STRING: %s\n", *str);
			if (!*str)
				return (NULL);
			else if (!*(*str))
				return (*str);
			//(*split)[ind] = *str;
			if (!aux_lead(lead, split, str))
				return (free_mem(*split), NULL);
			second = 0;
			i = -1;
		}
	}
	return (*str);
}

char	**expand_cli(char **words, t_env **lst_env)
{
	int	i;

	i = -1;
	while (words[++i])
	{
		if (words[i][0] == '$' && words[i][1] == '?' && !words[i][2])
			continue ;
		else if (i > 0 && ft_strcmp(words[i - 1], "<<") == 0)
		{
			words[i] = remove_quotes(words[i], words);
			if (!words[i])
				handle_expand_error(lst_env);
			continue ;
		}
		if (!check_if_expand(lst_env, &words[i], &words))
			handle_expand_error(lst_env);
		else
		{
			words[i] = remove_quotes(words[i], words);
			if (!words[i])
				handle_expand_error(lst_env);
		}
	}
	return (words);
}
