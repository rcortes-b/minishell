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
	int	counter;

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
	int	counter;

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
