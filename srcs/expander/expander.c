/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:23:16 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/26 17:23:18 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/parse.h"

//printf("malloc calc: %lu\n", ft_strlen(str) - j - 1 + ft_strlen(env) - j + 1);

static char	*do_expand(t_list **lst_env, char *str, int index)
{
	char	*env_name;
	char	*env;
	char	*new_str;
	int		i;
	int		j;

	i = index + 1;
	j = 0;
	while (str[i])
	{
		while (str[i + j] && str[i + j] != '$'
			&& str[i + j] != '"' && str[i + j] != '\'' && str[i + j] != ' ')
			j++;
		env_name = ft_substr(str, i, j);
		if (!env_name)
			return (NULL);
		env = get_env(lst_env, env_name);
		if (!env)
			return (NULL);
		new_str = malloc(ft_strlen(str) - j - 1 + ft_strlen(env) - j);
		new_str = get_expanded(new_str, env, str, index);
		free(str);
		return (new_str);
	}
	return (NULL);
}

void	check_if_expand(t_list **lst_env, char **str)
{
	int		i;
	char	lead;
	int		second;

	second = 0;
	lead = 'x'; //Delete this yavan
	i = -1;
	while (str[0][++i])
	{
		if (!second && (str[0][i] == '"' || str[0][i] == '\''))
		{
			lead = str[0][i];
			second = 1;
		}
		else if (second && str[0][i] == lead)
		{
			lead = 'x';
			second = 0;
		}
		if (str[0][i] == '$' && lead != '\'' )
		{
			*str = do_expand(lst_env, *str, i);
			second = 0;
			i = -1;
			printf("Str: %s\n", *str);
		}
	}
}

static char	*remove_quotes(char *str)
{
	char	lead;
	char	*new_comm;
	int		i;
	int		lead_counter;

	lead = 'x';
	lead_counter = 0;
	i = -1;
	while (str[++i])
	{
		while (str[i] && str[i] != '"' && str[i] != '\'')
			i++;
		if (str[i] == '\'' || str[i] == '"')
		{
			lead = str[i++];
			lead_counter++;
		}
		while (str[i] && str[i] != lead)
			i++;
	}
	new_comm = (char *)malloc(ft_strlen(str) - (lead_counter * 2) + 1);
	if (!new_comm)
		printf("loll error\n");
	return (del_quotes(str, new_comm));
}

static void	handle_expander(t_word **word, t_list **lst_env)
{
	int	i;

	i = 0;
	check_if_expand(lst_env, &(*word)->com);
	(*word)->com = remove_quotes((*word)->com);
	while ((*word)->flags[i])
	{
		check_if_expand(lst_env, &(*word)->flags[i]);
		(*word)->flags[i] = remove_quotes((*word)->flags[i]);
		i++;
	}
}

void	expand_cli(t_word **word, t_list **lst_env)
{
	t_word	*aux;

	aux = *word;
	while (aux)
	{
		if (aux->token == COMMAND)
			handle_expander(&aux, lst_env);
		aux = aux->next;
	}
}
