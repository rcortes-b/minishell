/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 10:45:06 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/21 10:45:07 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/parse.h"
#include "../../includes/error.h"

char	*aux_check_operator(char **new_split)
{
	char	*temp;
	int		j;

	temp = (char *)malloc(ft_strlen(*new_split) + 1 + 4);
	if (!temp)
		return (NULL);
	j = 0;
	temp[j++] = '"';
	temp[j++] = '!';
	while ((*new_split)[j - 2])
	{
		temp[j] = (*new_split)[j - 2];
		j++;
	}
	temp[j++] = '!';
	temp[j++] = '"';
	temp[j] = '\0';
	free(*new_split);
	return (temp);
}

static int	check_operator(char **new_split)
{
	int		i;

	i = -1;
	while (new_split[++i])
	{
		if (new_split[i][0] == '|'
			|| new_split[i][0] == '<' || new_split[i][0] == '>')
		{
			new_split[i] = aux_check_operator(&new_split[i]);
			if (!new_split[i])
				return (free_mem(new_split), 0);
		}
	}
	return (1);
}

static int	append_newstr(char **def_split, t_exp *exp, int size)
{
	int	i;

	exp->new_split = ft_calloc(sizeof(char *), size);
	if (!exp->new_split)
		return (free_mem(def_split), 0);
	i = -1;
	while (def_split[++i])
	{
		exp->new_split[i] = ft_strdup(def_split[i]);
		if (!exp->new_split[i])
			return (free_mem(def_split), free_mem(exp->new_split), 0);
	}
	exp->new_split[i] = NULL;
	free_mem(def_split);
	return (1);
}

static int	create_split(t_exp *exp, char **split_aux, char **def_split)
{
	int	counter;
	int	i;
	int	j;

	counter = -1;
	while (++counter < exp->new_index)
	{
		def_split[counter] = ft_strdup(exp->new_split[counter]);
		if (!def_split[counter])
			return (free_mem(def_split), 0);
	}
	j = counter + 1;
	i = 0;
	while (split_aux[i])
	{
		def_split[counter++] = ft_strdup(split_aux[i++]);
		if (!def_split[counter - 1])
			return (free_mem(def_split), 0);
	}
	if (!aux_create_split(exp, def_split, counter, j))
		return (0);
	free_mem(exp->new_split);
	return (free_mem(split_aux), 1);
}

int	modify_split(t_exp *exp, char *str)
{
	char	**split_aux;
	char	**def_split;
	int		j;
	int		i;

	split_aux = expsplit(exp, str);
	if (!split_aux)
		return (0);
	if (!check_operator(split_aux))
		return (0);
	i = 0;
	while (exp->new_split[i])
		i++;
	j = 0;
	while (split_aux[j])
		j++;
	def_split = ft_calloc(sizeof(char *), (i + j));
	if (!def_split)
		return (free_mem(split_aux), 0);
	if (!create_split(exp, split_aux, def_split))
		return (free_mem(split_aux), 0);
	if (!append_newstr(def_split, exp, i + j))
		return (free_mem(split_aux), 0);
	return (1);
}
