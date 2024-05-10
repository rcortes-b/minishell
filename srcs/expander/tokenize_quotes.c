/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 19:15:09 by rcortes-          #+#    #+#             */
/*   Updated: 2024/05/09 19:15:09 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/parse.h"

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

void	tokenize_quotes(t_exp *exp, int **tab, int index)
{
	int	size;
	int	limit;

	if (skip_quote(index, exp))
		return ;
	size = 1;
	if (exp->expanded_str[index] == '\'')
		limit = exp->q.s_counter;
	else
		limit = exp->q.d_counter;
	while (size - 1 < limit)
	{
		if ((*tab)[size - 1] == index)
			return ;
		size++;
	}
	*tab = copy_del_index(*tab, size, index);
	if (exp->expanded_str[index] == '\'')
		exp->q.s_counter = size;
	else
		exp->q.d_counter = size;
}

void	ignore_quotes(t_exp *exp, char lead, int index)
{
	char	quote;
	int		size;

	if (lead == '\'')
		quote = '"';
	else
		quote = '\'';
	size = 0;
	while (size < exp->q.skip_counter)
		size++;
	while (exp->expanded_str[index] && exp->expanded_str[index] != lead)
	{
		if (!skip_quote(index, exp) && exp->expanded_str[index] == quote)
		{
			size++;
			exp->q.skip_quote = copy_del_index(exp->q.skip_quote, size, index);
		}
		index++;
	}
	exp->q.skip_counter = size;
}

void	skip_quotes_update(t_exp *exp, t_env *env, int index, int name)
{
	int	update;
	int	counter;

	counter = 0;
	if (env)
		update = ft_strlen(env->value) - ft_strlen(env->key) - 1;
	else
		update = name * -1;
	while (counter < exp->q.skip_counter)
	{
		if (exp->q.skip_quote[counter] > index)
			exp->q.skip_quote[counter] += update;
		counter++;
	}
}

void	tokenize_split(t_exp *exp, char lead, int index, t_env *env)
{
	int	size;

	if (lead != 'x' || !env || !ft_strlen(env->value))
		return ;
	exp->is_split = 1;
	size = -1;
	while (++size < exp->exp_counter)
	{
		if (exp->exp_index[size] + exp->exp_value[size] > index)
		{
			exp->exp_value[size] = exp->exp_index[size]
				+ (ft_strlen(env->value) - 1) + (exp->exp_index[size]
					- exp->exp_value[size]);
			return ;
		}
	}
	size += 1;
	exp->exp_index = copy_del_index(exp->exp_index, size, index);
	exp->exp_value = \
	copy_del_index(exp->exp_value, size, ft_strlen(env->value) - 1);
	exp->exp_counter = size;
}
