/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:15:32 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/21 11:15:32 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/parse.h"

char	**expsplit(t_exp *exp, char *str)
{
	char	**split_aux;

	if (!str[0] && exp->q.d_del_index)
	{
		split_aux = (char **)malloc(sizeof(char *) * 2);
		if (!split_aux)
			return (NULL);
		split_aux[0] = ft_strdup("");
		if (!split_aux[0])
			return (free(split_aux), NULL);
		split_aux[1] = NULL;
	}
	else
		split_aux = expander_split(exp, str, ' ');
	if (!split_aux)
		return (NULL);
	return (split_aux);
}

static void	ambiguous_aux(int *trigger, int *j, int *i, char *str)
{
	if (!str)
		*trigger = 0;
	if (i && !str)
		*i = 1;
	if (j)
		*j = 0;
	if (*trigger == 1)
		*trigger = 0;
	if (str)
		iterate_expand(str, j, *i);
}

int	check_if_ambiguos(t_env **env, char **split, int index)
{
	t_env	*tmp;
	int		trigger;
	int		i;
	int		j;

	if (index == 0 || split[index][0] != '$')
		return (0);
	ambiguous_aux(&trigger, NULL, &i, NULL);
	while (split[index][i])
	{
		ambiguous_aux(&trigger, &j, &i, split[index]);
		tmp = get_env(env, ft_substr(split[index], i, j));
		if ((!tmp || (tmp && !tmp->value))
			&& (*split[index - 1] == '<' || *split[index - 1] == '>'))
			trigger = 1;
		if (split[index][i + j] == '$')
			i += j + 1;
		else if (!split[index][i + j])
			break ;
		else
			return (0);
	}
	if (trigger)
		return (1);
	return (0);
}

char	*expand_home(t_env **env, char *str)
{
	t_env	*home;
	char	*tmp_str;

	tmp_str = NULL;
	home = get_env(env, "HOME");
	if (str[1])
	{
		tmp_str = ft_strdup(&str[1]);
		if (!tmp_str)
			return (free(str), NULL);
	}
	free(str);
	if (!tmp_str)
		str = ft_strdup(home->value);
	else
	{
		str = ft_strjoin(home->value, tmp_str);
		free(tmp_str);
		if (!str)
			return (NULL);
	}
	if (!str)
		return (NULL);
	return (str);
}

int	expander_aux(t_exp *exp, t_env **lst_env, char *lead)
{
	int	i;
	int	second;

	i = -1;
	second = 0;
	while (exp->expanded_str[++i])
	{
		prep_expand(exp, &i, &second, lead);
		if ((exp->expanded_str[i] == '$' && *lead != '\'')
			&& exp->expanded_str[i + 1] && (ft_isalnum(exp->expanded_str[i + 1])
				|| (exp->expanded_str[i + 1] == '?')))
		{
			expansion_supreme(exp, &i, lst_env, *lead);
			second = 0;
			i = -1;
			continue ;
		}
		if (!exp->expanded_str[i])
			return (1);
	}
	return (1);
}
