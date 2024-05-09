/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
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

int	*set_dquote_values(int *tab_counter, int *i, int *j, int *tab)
{
	*tab_counter = 0;
	*i = -1;
	*j = 0;
	if (!tab)
		return (NULL);
	return (tab);
}

void	init_delvalues(int *i, int *new_counter, char *lead, int *j)
{
	*i = 0;
	*new_counter = 0;
	*lead = 'x';
	*j = 0;
}

void	update_index_expand(t_exp *exp)
{
	int	s_counter;
	int	d_counter;
	int	e_count;

	if (!exp->exp_index)
		return ;
	e_count = 0;
	while (e_count < exp->exp_counter)
	{
		s_counter = 0;
		while (s_counter < exp->q.s_counter)
		{
			if (exp->exp_index[e_count] > exp->q.del_index[s_counter])
				exp->exp_index[e_count] -= 2;
			s_counter++;
		}
		d_counter = 0;
		while (d_counter < exp->q.d_counter)
		{
			if (exp->exp_index[e_count] > exp->q.d_del_index[d_counter])
				exp->exp_index[e_count] -= 2;
			d_counter++;
		}
		e_count++;
	}
}

static int	iterate_token_spc(int *tab, int *index, char *str, int limit)
{
	if (str[*index] != ' ')
		return (0);
	while (str[*index] && str[*index] == ' ' && *index < limit)
	{
		tab[*index] = 1;
		(*index)++;
	}
	return (1);
}

void	tokenize_spaces(t_exp *exp, char *str)
{
	int	i;
	int	counter;

	if (!exp->is_split)
		return ;
	else if (!exp->exp_index)
		return (exp->spc = ft_calloc(sizeof(int), ft_strlen(str)), (void)0);
	counter = 0;
	i = -1;
	exp->spc = (int *)malloc(sizeof(int) * (ft_strlen(str) + 1));
	if (!exp->spc)
		return ;
	while (str[++i])
	{
		if (i == exp->exp_index[counter])
		{
			if (str[i] == ' ')
				exp->spc[i++] = 0;
			while (i < exp->exp_index[counter] + exp->exp_value[counter] && str[i] == ' ')
				exp->spc[i++] = 1;
			while (i < exp->exp_index[counter] + exp->exp_value[counter])
			{
				if (!iterate_token_spc(exp->spc, &i, str, exp->exp_index[counter] + exp->exp_value[counter]))
					exp->spc[i++] = 0;
			}
		}
		exp->spc[i] = 0;
	}
	exp->spc[i] = 0;
}
