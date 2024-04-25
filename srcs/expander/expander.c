/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 10:54:14 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/21 10:54:14 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/parse.h"
#include "../../includes/error.h"
#include "../../includes/builtins.h"

static int	init_newspl(t_exp *exp)
{
	int	i;

	i = 0;
	while (exp->og_split[i])
		i++;
	exp->new_split = ft_calloc(sizeof(char *), i + 1);
	if (!exp->new_split)
		return (0);
	i = -1;
	while (exp->og_split[++i])
	{
		exp->new_split[i] = ft_strdup(exp->og_split[i]);
		if (!exp->new_split[i])
			return (free_mem(exp->new_split), 0);
	}
	exp->new_split[i] = NULL;
	return (1);
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
	while (str[k])
		new_str[i++] = str[k++];
	new_str[i] = '\0';
	return (new_str);
}

char	*do_expand(t_env **lst_env, char *str, int index, t_exp *exp)
{
	t_env	*env;
	char	*env_name;
	char	*new_str;
	int		j;

	j = 0;
	iterate_expand(str, &j, index + 1);
	env_name = ft_substr(str, index + 1, j);
	if (!env_name)
		return (free(str), NULL);
	env = get_env(lst_env, env_name);
	if (env)
		new_str = malloc(ft_strlen(str)
				+ ft_strlen(env->value) - ft_strlen(env->key));
	else
	{
		new_str = NULL;
		return (invalid_env(new_str, env_name, str, index));
	}
	if (!new_str)
		return (free(str), free(env_name), NULL);
	new_str = get_expanded(new_str, env, exp->expanded_str, index);
	free(exp->expanded_str);
	free(env_name);
	return (new_str);
}

static int	check_if_expand(t_env **lst_env, t_exp *exp, char *str)
{
	char	lead;

	exp->expanded_str = ft_strdup(str);
	if (str[0] == '~' && (!str[1] || str[1] == '/'))
	{
		exp->is_split = 1;
		exp->expanded_str = expand_home(lst_env, exp->expanded_str);
	}
	if (!exp->expanded_str)
		return (0);
	lead = 'x';
	if (!expander_aux(exp, lst_env, str, &lead))
		return (0);
	if (exp->new_index < exp->index)
		exp->new_index = exp->index;
	if (exp->is_split && !modify_split(exp, exp->expanded_str))
		return (free(exp->expanded_str), 0);
	free(exp->expanded_str);
	return (1);
}

char	**lets_expand(t_env **lst_env, char **split)
{
	t_exp	exp;

	exp.og_split = split;
	exp.index = -1;
	exp.new_index = 0;
	if (!init_newspl(&exp))
		return (free_mem(split), NULL);
	while (exp.og_split[++exp.index])
	{
		exp.is_first = 1;
		exp.is_split = 0;
		if (exp.og_split[exp.index][0] == '$'
			&& exp.og_split[exp.index][1] == '?' && !exp.og_split[exp.index][2])
			continue ;
		else if (exp.index > 0
			&& ft_strcmp(exp.og_split[exp.index - 1], "<<") == 0)
			continue ;
		if (check_if_ambiguos(lst_env, split, exp.index))
			continue ;
		if (!check_if_expand(lst_env, &exp, exp.og_split[exp.index]))
			return (free_mem(split), free_mem(exp.new_split), NULL);
	}
	if (!remove_quotes(exp.new_split))
		return (free_mem(exp.new_split), NULL);
	return (free_mem(exp.og_split), exp.new_split);
}
