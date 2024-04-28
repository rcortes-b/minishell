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
//	if (!exp->is_split)
	//	exp->expanded_str = prep_quotes(exp->expanded_str, (*i), exp);
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

static int	*copy_del_index(int *tab, int size, int new_value)
{
	int	*new;
	int	i;

	new = (int *)malloc(sizeof(int) * (size + 1));
	if (!new)
		return (0);
	i = -1;
	while (++i < size - 1)
		new[i] = tab[i];
	new[i++] = new_value;
	new[i] = 0;
	if (tab)
		free(tab);
	return (new);
}

/* quiero hacer update del indice doonde se encuentra cada single quote */

void	update_del_index(t_exp *exp, int i, int **tab, char lead)
{
	int	size;
	int	ind;
	int	limit;

	(void)exp;
	size = 1;
	ind = -1;
	i -= 1;
	while ((exp->expanded_str[i] != lead || skip_quote(i, exp)) && i > 0)
		i--;
	if (lead == '\'')
		limit = exp->s_counter;
	else
		limit = exp->d_counter;
	while (size - 1 < limit)
	{
		size++;
	}
	*tab = copy_del_index(*tab, size, i);
	if (lead == '\'')
		exp->s_counter = size;
	else
		exp->d_counter = size;
}

char	*delete_remain_quotes(t_exp *exp, int *tab, char lead, int limit_counter)
{
	char	*new;
	int		size;
	int		i;
	int		j;
	int		tab_counter;

	size = 0;
	tab_counter = 0;
	if (!tab)
		return (exp->expanded_str);
	printf("limit cnter: %d\n", limit_counter);
	while (tab && size < limit_counter)
		size++;
	new = malloc(ft_strlen(exp->expanded_str) - (size * 2) + 1);
	if (!new)
		return (NULL);
	i = -1;
	j = 0;
	while (exp->expanded_str[++i])
	{
		if (i == tab[tab_counter])
		{
			tab_counter++;
			while (exp->expanded_str[++i] != lead || skip_quote(i, exp))
				new[j++] = exp->expanded_str[i];
		}
		else
			new[j++] = exp->expanded_str[i];
	}
	new[j] = '\0';
	free(exp->expanded_str);
	return (new);
}

int	check_if_delquote(char *str, int i, char lead, t_exp *exp)
{
	if (lead != '\"')
		return (0);
	while (str[i] != '"')
	{
		if (str[i] == '\'' && !skip_quote(i, exp))
			return (1);
		i++;
	}
	if (str[i] == '"')
	{
		if (is_ddel_quote(str, i, exp))
			return (1);
	}
	return  (0);
}

void	update_index_to_del(t_exp *exp)
{
	int	s_counter;
	int	d_counter;

	if (!exp->del_index || !exp->d_del_index)
		return ;
	s_counter = 0;
	while (s_counter < exp->s_counter)
	{
		d_counter = 0;
		while (d_counter < exp->d_counter)
		{
			if (exp->del_index[s_counter] < exp->d_del_index[d_counter])
				exp->d_del_index[d_counter] -= 2;
			d_counter++;
		}
		s_counter++;
	}	
}

int	*create_new_skip(t_exp *exp, int index, t_env *env, int quote_counter)
{
	int	*new;
	int	size;
	int	i;

	new = malloc(sizeof(int) * (exp->skip_counter + quote_counter + 1));
	if (!new)
		return (NULL);
	size = -1;
	while (++size < exp->skip_counter)
		new[size] = exp->expanded_quote[size];
	i = 0;
	while (env->value[i])
	{
		if (env->value[i] == '"' || env->value[i] == '\'')
			new[size++] = index + i;
		i++;
	}
	new[size] = 0;
	if (exp->expanded_quote)
		free(exp->expanded_quote);
	return (new);
}

void	skip_index_expquote(t_exp *exp, int index, t_env *env)
{
	int	i;
	int	quote_counter;

	quote_counter = 0;
	i = -1;
	while (env->value && env->value[++i])
	{
		if (env->value[i] == '"' || env->value[i] == '\'')
			quote_counter++;
	}
	if (!quote_counter)
		return ;
	exp->expanded_quote = create_new_skip(exp, index, env, quote_counter);
	exp->skip_counter += quote_counter;
}

int	skip_quote(int i, t_exp *exp)
{
	int counter;

	counter = 0;
	while (counter < exp->skip_counter)
	{
		if (exp->expanded_quote[counter] == i)
			return (1);
		counter++;
	}
	return (0);
}

int	is_ddel_quote(char *str, int i, t_exp *exp)
{
	int	counter;

	i--;
	while (str[i] != '"')
		i--;
	counter = 0;
	while (counter < exp->d_counter)
	{
		if (i == exp->d_del_index[counter])
			return (1);
		counter++;
	}
	return (0);
}

int	is_dquote(char *str, int i, t_exp *exp)
{
	int counter;

	counter = 0;
	if (str[i] == '"')
	{
		while (counter < exp->d_counter)
		{
			if (exp->d_del_index[counter] == i)
				return (1);
			counter++;
		}
	}
	else if (str[i] == '\'')
	{
		while (counter < exp->s_counter)
		{
			if (exp->del_index[counter] == i)
				return (1);
			counter++;
		}
	}
	return (0);
}
