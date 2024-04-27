/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
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

void	prep_quotes_aux(char *str, char *lead,
		int *lead_counter, int *index)
{
	if (str[*index] == '\'' || str[*index] == '"')
	{
		*lead = str[(*index)++];
		(*lead_counter)++;
	}
}

char	*set_do_expand(int *j, int *index, char *str, int *is_quote)
{
	char	*env_name;

	*j = 0;
	*is_quote = 0;
	if (str[(*index)] == '$')
		*is_quote = 1;
	iterate_expand(str, j, (*index) + (*is_quote));
	env_name = ft_substr(str, (*index) + (*is_quote), (*j));
	if (!(*is_quote))
		(*index)--;
	return (env_name);
}

char	*new_operator(char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(ft_strlen(str) + 3);
	if (!new)
		return (NULL);
	new[i] = str[i];
	i += 1;
	new[i++] = '!';
	while (str[i - 1] != '\"')
	{
		new[i] = str[i - 1];
		i++;
	}
	new[i++] = '!';
	new[i++] = '\"';
	new[i] = '\0';
	free(str);
	return (new);
}
