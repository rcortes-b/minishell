/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 09:51:08 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/04 09:51:09 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/parse.h"
#include "../../includes/error.h"

void	free_node(t_env **node)
{
	free((*node)->key);
	free((*node)->value);
	free(*node);
}

static char	*aux_check_pipe(char **new_split)
{
	char	*temp;
	int		j;

	temp = (char *)malloc(ft_strlen(*new_split) + 1 + 2);
	if (!temp)
		return (NULL);
	j = 0;
	temp[j++] = '"';
	while ((*new_split)[j - 1])
	{
		temp[j] = (*new_split)[j - 1];
		j++;
	}
	temp[j++] = '"';
	temp[j] = '\0';
	free(*new_split);
	return (temp);
}

static int	check_pipe(char **new_split)
{
	char	**aux;
	int		i;

	aux = new_split;
	i = -1;
	while (new_split[++i])
	{
		if (new_split[i][0] == '|' || new_split[i][0] == '<' || new_split[i][0] == '>')
		{
			new_split[i] = aux_check_pipe(&new_split[i]);
			if (!new_split[i])
				return (0);
		}
	}
	return (1);
}

static char	**create_split(char **def_split, char **split,
	char **new_split, char *str)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (split[++i] != str)
		def_split[i] = split[i];
	k = i + 1;
	j = 0;
	while (new_split[j])
		def_split[i++] = new_split[j++];
	while (split[k])
		def_split[i++] = split[k++];
	def_split[i] = NULL;
	free(str);
	free(new_split);
	free(split);
	return (def_split);
}

//str es el pointer a la palabra expandida no al head del array

char	**resplit(char **str, char ***split)
{
	char	**new_split;
	char	**def_split;
	int		counter;
	int		i;

	new_split = ft_esplit(*str, ' ');
	if (!new_split)
		return (NULL);
	if (!check_pipe(new_split))
		return (free_mem(new_split), NULL);
	i = 0;
	while ((*split)[i])
		i++;
	counter = 0;
	while (new_split[counter])
		counter++;
	def_split = (char **)malloc(sizeof(char *) * (i + counter));
	if (!def_split)
		return (free_mem(new_split), NULL);
	def_split = create_split(def_split, *split, new_split, *str);
	return (def_split);
}
