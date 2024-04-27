/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:36:05 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/21 15:36:07 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"
#include "../../includes/expander.h"

static char	*trim_operator(char *str)
{
	char	*new;
	int		i;

	i = 0;
	while (str[i + 2] != '!')
		i++;
	new = malloc(i + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (str[i + 2] != '!')
	{
		new[i] = str[i + 2];
		i++;
	}
	new[i] = '\0';
	free(str);
	return (new);
}

void	parse_operators(t_word **words)
{
	t_word	*aux;
	int		i;

	aux = *words;
	while (aux)
	{
		if (is_operator(aux->com, 1))
		{
			aux->com = trim_operator(aux->com);
			if (!aux->com)
				return ;
		}
		i = -1;
		while (aux->flags && aux->flags[++i])
		{
			if (is_operator(aux->flags[i], 1))
			{
				aux->flags[i] = trim_operator(aux->flags[i]);
				if (!aux->flags[i])
					return ;
			}
		}
		aux = aux->next;
	}
}

int	is_operator(char *new_split, int is_inquote)
{
	if (is_inquote == 0)
	{
		if ((ft_strcmp(new_split, "|") == 0)
			|| (ft_strcmp(new_split, "<") == 0)
			|| (ft_strcmp(new_split, "<<") == 0)
			|| (ft_strcmp(new_split, ">") == 0)
			|| (ft_strcmp(new_split, ">>") == 0))
			return (1);
	}
	else if (is_inquote == 1)
	{
		if ((ft_strcmp(new_split, "\"!|!\"") == 0)
			|| (ft_strcmp(new_split, "\"!<!\"") == 0)
			|| (ft_strcmp(new_split, "\"!<<!\"") == 0)
			|| (ft_strcmp(new_split, "\"!>!\"") == 0)
			|| (ft_strcmp(new_split, "\"!>>!\"") == 0))
			return (1);
	}
	return (0);
}

int	is_symbol(t_operators *data, char c)
{
	if (c == data->reinput || c == data->reoutput || c == data->pipe)
		return (1);
	return (0);
}

void	init_data(t_operators *data, char **envp)
{
	data->pipe = '|';
	data->squote = '\'';
	data->dquote = '"';
	data->reinput = '<';
	data->reoutput = '>';
	data->og_env = envp;
}
