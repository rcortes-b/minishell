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

/*static void	set_expand_values(char *lead, int *quote,
		char c, int value, int *index)
{
	*lead = c;
	*quote = value;
	if (index)
		*index = -1;
}*/

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
		iterate_expand(str, &j, i);
		env_name = ft_substr(str, i, j);
		if (!env_name)
			return (NULL);
		env = get_env(lst_env, env_name);
		if (!env)
			return (invalid_env(&str, &env_name));
		new_str = malloc(ft_strlen(str) + ft_strlen(env->value)
				- ft_strlen(env->key) - 1);
		if (!new_str)
			return (free(env_name), NULL);
		new_str = get_expanded(new_str, env, str, index);
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
		if (str[0][i] == '$' && lead != '\'' )
		{
			*str = do_expand(lst_env, *str, i);
			if (!*str)
				return (NULL);
			else if (!*(*str))
				return (*str);
			else if (!aux_lead(lead, split, str))
				return (NULL);
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
		if (!check_if_expand(lst_env, &words[i], &words))
			handle_env_error(lst_env, words);
		else
			words[i] = remove_quotes(words[i]);
	}
	return (words);
}

static char	*del_quotes(char *str, char *new_str)
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
}

char	*remove_quotes(char *str)
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
