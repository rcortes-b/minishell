#include "../../includes/expander.h"
#include "../../includes/parse.h"

//printf("malloc calc: %lu\n", ft_strlen(str) - j - 1 + ft_strlen(env) - j + 1);
static char	*get_expanded(char *new_str, char *env, char *str)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (str[++i] != '$')
		new_str[i] = str[i];
	j = 0;
	while(env[j] != '=')
		j++;
	j++;
	k = j + i;
	while (env[j])
		new_str[i++] = env[j++];
	j = 1;
	while (str[k])
		new_str[i++] = str[k++];
	new_str[i] = '\0';
	return (new_str);
}

static char	*do_expand(t_list **lst_env, char *str)
{
	char	*env_name;
	char	*env;
	char	*new_str;
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			i++;
			j = 0;
			while (str[i + j] && str[i + j] != '$')
				j++;
			env_name = ft_substr(str, i, j);
			if (!env_name)
				return (NULL);
			env = get_env(lst_env, env_name);
			if (!env)
				return (NULL);
			new_str = (char *)malloc(ft_strlen(str) - j - 1 + ft_strlen(env) - j);
			new_str = get_expanded(new_str, env, str);
			return (new_str);
		}
	}
	return (NULL);
}

static char	*check_if_expand(t_list **lst_env, char *str)
{
	int		i;
	char	lead;
	char	*aux;

	i = -1;
	if (str[0] == '"')
		lead = '"';
	else if (str[0] == '\'')
		lead = '\'';
	else
		lead = 'a';
	while (str[++i])
	{
		if (str[i] == '$' && lead != '\'')
		{
			aux = do_expand(lst_env, str);
			free(str);
			str = aux;
			i = -1;
		}
	}
	printf("Str: %s\n", str);
	return (str);
}
static char	*remove_quotes(char *str)
{

	char	*new_comm;
	int		i;
	int		quote_counter;

	quote_counter = 0;
	i = -1;
	while (str[++i] == '"' || str[i] == '\'')
		quote_counter++;
	new_comm = (char *)malloc(ft_strlen(str) - quote_counter + 1);
	if (!new_comm)
		printf("loll error\n");
	return ("perro");
}

static void	handle_expander(t_word **word, t_list **lst_env)
{
	int	i;
	
	//comm
	i = 0;
	check_if_expand(lst_env, (*word)->com);
	remove_quotes((*word)->com);
	//flags
	while ((*word)->flags[i])
	{
		check_if_expand(lst_env, (*word)->flags[i]);
		remove_quotes((*word)->flags[i]);
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