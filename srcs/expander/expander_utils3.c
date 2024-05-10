/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvallhon <mvallhon@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:22:13 by mvallhon          #+#    #+#             */
/*   Updated: 2024/04/28 15:22:20 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/parse.h"
#include "../../includes/error.h"

void	set_exp(t_exp *exp)
{
	exp->q.skip_quote = NULL;
	exp->q.del_index = NULL;
	exp->q.d_del_index = NULL;
	exp->is_first = 1;
	exp->is_split = 0;
	exp->q.s_counter = 0;
	exp->q.d_counter = 0;
	exp->q.skip_counter = 0;
	exp->exp_index = NULL;
	exp->exp_value = NULL;
	exp->spc = NULL;
	exp->exp_counter = 0;
}

int	quote_conditions(t_exp *exp)
{
	if (exp->new_index < exp->index)
		exp->new_index = exp->index;
	update_index_expand(exp);
	update_index_to_del(exp);
	if (exp->q.del_index)
		exp->expanded_str = \
		delete_remain_quotes(exp, exp->q.del_index, '\'', exp->q.s_counter);
	if (exp->q.d_del_index)
		exp->expanded_str = \
	delete_remain_quotes(exp, exp->q.d_del_index, '"', exp->q.d_counter);
	tokenize_spaces(exp, exp->expanded_str);
	if (exp->is_split && !modify_split(exp, exp->expanded_str))
		return (free(exp->expanded_str), 0);
	return (1);
}

void	prep_expand(t_exp *exp, int *i, int *second, char *lead)
{
	if (skip_quote(*i, exp))
		(*i)++;
	exp->quote_amount = 0;
	if (!(*second) && (exp->expanded_str[*i] == '"'
			|| exp->expanded_str[*i] == '\''))
	{
		set_expand_values(lead, second, exp->expanded_str[*i], NULL);
		if (exp->expanded_str[*i] == '\'')
			tokenize_quotes(exp, &exp->q.del_index, *i);
		else
			tokenize_quotes(exp, &exp->q.d_del_index, *i);
		ignore_quotes(exp, exp->expanded_str[*i], *i + 1);
	}
	else if (second && exp->expanded_str[*i] == *lead)
		set_expand_values(lead, second, 'x', NULL);
}

void	free_expander(t_exp *exp)
{
	free(exp->expanded_str);
	if (exp->q.del_index)
		free(exp->q.del_index);
	if (exp->q.d_del_index)
		free(exp->q.d_del_index);
	if (exp->q.skip_quote)
		free(exp->q.skip_quote);
	if (exp->spc)
		free(exp->spc);
	if (exp->exp_index)
		free(exp->exp_index);
	if (exp->exp_value)
		free(exp->exp_value);
}

char	*expanded_str(t_exp *exp, t_env *env, char *new_str, int index)
{
	new_str = get_expanded(new_str, env, exp->expanded_str, index);
	skip_index_expquote(exp, index, env);
	free(exp->expanded_str);
	return (new_str);
}
