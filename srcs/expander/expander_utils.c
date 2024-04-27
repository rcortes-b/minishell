/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 10:43:36 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/21 10:43:36 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/parse.h"
#include "../../includes/error.h"

char	*invalid_env(char *new_str, char *env_name, char *str, int index)
{
	int		key_len;
	int		k;
	int		i;

	i = -1;
	new_str = malloc(ft_strlen(str) - ft_strlen(env_name));
	if (!new_str)
		return (free(str), free(env_name), NULL);
	while (++i < index)
		new_str[i] = str[i];
	key_len = ft_strlen(env_name);
	k = i + key_len + 1;
	while (str[k])
		new_str[i++] = str[k++];
	new_str[i] = '\0';
	free(env_name);
	free(str);
	return (new_str);
}

void	iterate_expand(char *str, int *j, int i)
{
	while (str[i + *j]
		&& (ft_isalnum(str[i + *j]) == 1 || str[i + *j] == '_'))
		(*j)++;
}

void	set_expand_values(char *lead, int *quote, char c, int *index)
{
	if (c == 'x')
		*quote = 0;
	else
		*quote = 1;
	*lead = c;
	if (index)
		*index = -1;
}

int	is_expanded(char const *s1, char const *s2)
{
	int	size_s1;
	int	size_s2;

	if (!s1[0])
		return (0);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	if (s1[size_s1 - 1] == s2[size_s2 - 1])
		;
	else if ((s1[size_s1 - 1] == '\'' || s1[size_s1 - 1] == '"') && (!(s2[size_s2 - 1] == '\'' && s2[size_s2 - 1] == '"')))
		size_s1--;
	while (size_s2 > 0 && size_s1 > 0)
	{
		if (s1[--size_s1] != s2[--size_s2])
			return (1);
	}
	return (0);
}

int	aux_create_split(t_exp *exp, char **def_split, int counter, int j)
{
	exp->new_index = counter;
	printf("expnewindex: %d\n", exp->new_index);
	while (exp->new_split[j])
	{
		def_split[counter++] = ft_strdup(exp->new_split[j++]);
		if (!def_split[counter - 1])
			return (free_mem(def_split), 0);
	}
	def_split[counter] = NULL;
	return (1);
}
