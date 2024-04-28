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
	exp->expanded_quote = NULL;
	exp->del_index = NULL;
	exp->d_del_index = NULL;
	exp->is_first = 1;
	exp->is_split = 0;
	exp->s_counter = 0;
	exp->d_counter = 0;
	exp->skip_counter = 0;
}

int	quote_conditions(t_exp *exp)
{
	if (exp->new_index < exp->index)
		exp->new_index = exp->index;
	update_index_to_del(exp);
	if (exp->is_split && exp->del_index)
		exp->expanded_str = \
		delete_remain_quotes(exp, exp->del_index, '\'', exp->s_counter);
	if (exp->is_split && exp->d_del_index)
		exp->expanded_str = \
	delete_remain_quotes(exp, exp->d_del_index, '"', exp->d_counter);
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
		set_expand_values(lead, second, exp->expanded_str[*i], NULL);
	else if (second && exp->expanded_str[*i] == *lead)
		set_expand_values(lead, second, 'x', NULL);
}
