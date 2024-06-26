/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
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

int	*create_new_skip(t_exp *exp, int index, t_env *env, int quote_counter)
{
	int	*new;
	int	size;
	int	i;

	new = malloc(sizeof(int) * (exp->q.skip_counter + quote_counter + 1));
	if (!new)
		return (NULL);
	size = -1;
	while (++size < exp->q.skip_counter)
		new[size] = exp->q.skip_quote[size];
	i = 0;
	while (env->value[i])
	{
		if (env->value[i] == '"' || env->value[i] == '\'')
			new[size++] = index + i;
		i++;
	}
	new[size] = 0;
	if (exp->q.skip_quote)
		free(exp->q.skip_quote);
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
	exp->q.skip_quote = create_new_skip(exp, index, env, quote_counter);
	exp->q.skip_counter += quote_counter;
}

int	skip_quote(int i, t_exp *exp)
{
	int	counter;

	counter = 0;
	while (counter < exp->q.skip_counter)
	{
		if (exp->q.skip_quote[counter] == i)
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
	while (counter < exp->q.d_counter)
	{
		if (i == exp->q.d_del_index[counter])
			return (1);
		counter++;
	}
	return (0);
}

void	tokenize_spaces_aux(t_exp *exp, char *str, int *i, int *counter)
{
	if (str[*i] == ' ')
		exp->spc[(*i)++] = 0;
	while (*i < exp->exp_index[*counter] + exp->exp_value[*counter]
		&& str[*i] == ' ')
		exp->spc[(*i)++] = 1;
	while (*i < exp->exp_index[*counter] + exp->exp_value[*counter])
	{
		if (!iterate_token_spc(exp->spc, i, str, \
		exp->exp_index[*counter] + exp->exp_value[*counter]))
			exp->spc[(*i)++] = 0;
	}
	if (*counter < exp->exp_counter)
		(*counter)++;
}
