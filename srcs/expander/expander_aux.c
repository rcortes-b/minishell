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

int	
expander_aux(t_exp *exp, t_env **lst_env, char *str, char *lead)
{
	int	i;
	int	second;

	i = -1;
	second = 0;
	while (exp->expanded_str[++i])
	{
		if (!second && (exp->expanded_str[i] == '"'
				|| exp->expanded_str[i] == '\'') && !is_expanded(str, &exp->expanded_str[i]))
			set_expand_values(lead, &second, exp->expanded_str[i], NULL);
		else if (second && exp->expanded_str[i] == *lead)
			set_expand_values(lead, &second, 'x', NULL);
		if ((exp->expanded_str[i] == '$' && *lead != '\'')
			&& (exp->is_first == 1 || !is_expanded(str, &exp->expanded_str[i])))
		{
			exp->expanded_str = do_expand(lst_env, exp->expanded_str, i, exp);
			if (!exp->expanded_str)
				return (0);
			exp->is_split = 1;
			exp->is_first = 0;
			second = 0;
			i = -1;
			printf("EXPANDED: %s\nSTR: %s\n", exp->expanded_str, str);
		}
	}
	return (1);
}
