/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:51:02 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/27 15:51:04 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/parse.h"
#include "../../includes/error.h"

void	prep_quotes_aux(char *str, char *lead,
		int *lead_counter, int *index)
{
	if (str[*index] == '\'' || str[*index] == '"')
	{
		*lead = str[(*index)++];
		(*lead_counter)++;
	}
}

char	*set_do_expand(int *j, int *index, char *str, int *is_quote)
{
	char	*env_name;

	*j = 0;
	*is_quote = 0;
	if (str[(*index)] == '$')
		*is_quote = 1;
	iterate_expand(str, j, (*index) + (*is_quote));
	env_name = ft_substr(str, (*index) + (*is_quote), (*j));
	if (!(*is_quote))
		(*index)--;
	return (env_name);
}

char	*new_operator(char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(ft_strlen(str) + 3);
	if (!new)
		return (NULL);
	new[i] = str[i];
	i += 1;
	new[i++] = '!';
	while (str[i - 1] != '\"')
	{
		new[i] = str[i - 1];
		i++;
	}
	new[i++] = '!';
	new[i++] = '\"';
	new[i] = '\0';
	free(str);
	return (new);
}

void	is_not_split(t_exp *exp)
{
	if (!is_quoted_operator(exp->new_split[exp->new_index]))
	{
		exp->new_split[exp->new_index] = \
		prep_quotes(exp->new_split[exp->new_index], -1, NULL);
		exp->new_index++;
	}
	else
		exp->new_split[exp->new_index] = \
		new_operator(exp->new_split[exp->new_index]);
}

int	expansion_supreme(t_exp *exp, int *i, t_env **lst_env, char lead)
{
	if (!check_if_delquote(exp->expanded_str, *i, lead, exp))
		exp->expanded_str = rm_quotes_expand(exp, exp->expanded_str, *i);
	else
		update_del_index(exp, *i, &exp->d_del_index, '"');
	resize_index(exp, exp->expanded_str, i);
	exp->expanded_str = do_expand(lst_env, exp->expanded_str, *i, exp);
	if (!exp->expanded_str)
		return (0);
	exp->is_split = 1;
	exp->is_first = 0;
	return (1);
}
