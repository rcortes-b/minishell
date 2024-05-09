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

int	check_if_ambiguos(t_env **env, char **split, int index)
{
	t_env	*tmp;

	if (index == 0 || split[index][0] != '$')
		return (0);
	tmp = get_env(env, &split[index][1]);
	if ((!tmp || (tmp && !tmp->value))
		&& (*split[index - 1] == '<' || *split[index - 1] == '>'))
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
			&& exp->expanded_str[i + 1] && (ft_isalnum(exp->expanded_str[i + 1]) || (exp->expanded_str[i + 1] == '?')))
		{
			expansion_supreme(exp, &i, lst_env, *lead);
			second = 0;
			i = -1;
		}
	}
	return (1);
}
