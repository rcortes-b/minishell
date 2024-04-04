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

void	free_node(t_env **node)
{
	free((*node)->key);
	free((*node)->value);
	free(*node);
}

static void	check_pipe(char **new_split)
{
	char	**aux;
	char	*temp;
	int		i;
	int		j;

	aux = new_split;
	i = -1;
	while (new_split[++i])
	{
		if (new_split[i][0] == '|')
		{
			temp = (char *)malloc(ft_strlen(new_split[i]) + 1 + 2);
			/*if (!temp)
				idk????*/
			j = 0;
			temp[j] = '"';
			j++;
			while(new_split[i][j - 1])
			{
				temp[j] = new_split[i][j - 1];
				j++;
			}
			temp[j++] = '"';
			temp[j] = '\0';
			free(new_split[i]);
			new_split[i] = temp;
		}
	}
}
static char	**create_split(char **def_split, char **split, char **new_split, char *str)
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
	check_pipe(new_split);
	i = 0;
	while ((*split)[i])
		i++;
	counter = 0;
	while (new_split[counter])
		counter++;
	def_split = (char **)malloc(sizeof(char *) * (i  + counter));
	if (!def_split)
		return NULL; //temp
	def_split = create_split(def_split, *split, new_split, *str);
	return (def_split);
}

/*	i = -1;
	counter = 0;
	while (new_split[++i])
		counter += ft_strlen(new_split[i]);
	new = (char *)malloc(sizeof(char) * counter + 1);
	i = -1;
	j = 0;
	while(new_split[++i])
	{
		counter = 0;
		while (new_split[i][counter])
			new[j++] = new_split[i][counter++];
		if (new_split[i + 1] != NULL)
			new[j++] = ' ';
	}
	new[j] = '\0';
	free(*str);
	printf("newsplit: %s\n", new);
	return (new);*/