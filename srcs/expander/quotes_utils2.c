/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils2.c                                    :+:      :+:    :+:   */
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

	size = 1;
	ind = -1;
	i -= 1;
	while ((exp->expanded_str[i] != lead || skip_quote(i, exp)) && i > 0)
		i--;
	if (lead == '\'')
		limit = exp->q.s_counter;
	else
		limit = exp->q.d_counter;
	while (size - 1 < limit)
	{
		size++;
	}
	*tab = copy_del_index(*tab, size, i);
	if (lead == '\'')
		exp->q.s_counter = size;
	else
		exp->q.d_counter = size;
}

char	*delete_remain_quotes(t_exp *exp, int *tab,
		char lead, int limit_counter)
{
	char	*new;
	int		i;
	int		j;
	int		tab_counter;

	if (!set_dquote_values(&tab_counter, &i, &j, tab))
		return (exp->expanded_str);
	new = malloc(ft_strlen(exp->expanded_str) - (limit_counter * 2) + 1);
	if (!new)
		return (NULL);
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
	while (str[i] && str[i] != '"')
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
	return (0);
}

void	update_index_to_del(t_exp *exp)
{
	int	s_counter;
	int	d_counter;

	if (!exp->q.del_index || !exp->q.d_del_index)
		return ;
	s_counter = 0;
	while (s_counter < exp->q.s_counter)
	{
		d_counter = 0;
		while (d_counter < exp->q.d_counter)
		{
			if (exp->q.del_index[s_counter] < exp->q.d_del_index[d_counter])
				exp->q.d_del_index[d_counter] -= 2;
			d_counter++;
		}
		s_counter++;
	}
}
