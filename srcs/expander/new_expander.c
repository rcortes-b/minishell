#include "../../includes/expander.h"
#include "../../includes/parse.h"
#include "../../includes/error.h"

static int	is_expanded(char const *s1, char const *s2)
{
	int size_s1;
	int	size_s2;

	if (!s1[0])
		return (0);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	while (size_s2 > 0 && size_s1 > 0)
	{
		if (s1[--size_s1] != s2[--size_s2])
			return (1);
	}
	return (0);
}

static char	*invalid_env(char *new_str, char *env_name, char *str, int index)
{
	int		key_len;
	int		k;
	int		i;

	i = -1;
	new_str = malloc(ft_strlen(str) - ft_strlen(env_name) - 1);
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
	while (str[i + *j] && str[i + *j] != '$'
		&& str[i + *j] != '"' && str[i + *j] != '\'' && str[i + *j] != ' ')
		(*j)++;
}

static void	set_expand_values(char *lead, int *quote, char c, int *index)
{
	if (c == 'x')
		*quote = 0;
	else
		*quote = 1;
	*lead = c;
	if (index)
		*index = -1;
}

char	*get_expanded(char **new_str, t_env *env, char *str, int index)
{
	int	i;
	int	j;
	int	k;
	int	key_len;

	i = -1;
	while (++i < index)
		(*new_str)[i] = str[i];
	j = 0;
	key_len = ft_strlen(env->key);
	k = i + key_len + 1;
	while (env->value[j])
		(*new_str)[i++] = env->value[j++];
	while (str[k])
		(*new_str)[i++] = str[k++];
	(*new_str)[i] = '\0';
	return (*new_str);
}

static char	*do_expand(t_env **lst_env, t_exp *exp, char *str, int index)
{
	t_env	*env;
	char	*env_name;
	char	*new_str;
	int		j;

	j = 0;
	iterate_expand(str, &j, index + 1);
	env_name = ft_substr(str, index + 1, j);	
	if (!env_name)
		return (free(str), NULL);
	env = get_env(lst_env, env_name);
	if (env)
		new_str = malloc(ft_strlen(str) + ft_strlen(env->value)
			- ft_strlen(env->key) - 1);
	else
	{
		new_str = NULL;
		return (invalid_env(new_str, env_name, str, index));
	}
	if (!new_str)
		return (free(str), free(env_name), NULL);
	new_str = get_expanded(&new_str, env, str, index);
	free(exp->expanded_str);
	free(env_name);
	return (new_str);
}

static int	check_if_expand(t_env **lst_env, t_exp *exp, char *str, int il) //do handle_errors //il no sirve de na
{
	int		i;
	char	lead;
	int		second;

	exp->expanded_str = ft_strdup(str);
	if (!exp->expanded_str)
		return (0);
	set_expand_values(&lead, &second, 'x', &i);
	while (exp->expanded_str[++i])
	{
		if (!second && (exp->expanded_str[i] == '"' || exp->expanded_str[i] == '\''))
			set_expand_values(&lead, &second, exp->expanded_str[i], NULL);
		else if (second && exp->expanded_str[i] == lead)
			set_expand_values(&lead, &second, 'x', NULL);
		if ((exp->expanded_str[i] == '$' && lead != '\'') && (exp->is_first == 1 || !is_expanded(str, &exp->expanded_str[i])))
		{
			exp->expanded_str = do_expand(lst_env, exp, exp->expanded_str, i);
			if (!exp->expanded_str)
				return (0); //si es invalid env
			exp->is_first = 0;
			second = 0;
			i = -1;
		}
	}
	if (il == 1)
	{
		exp->new_split[1] = ft_strdup(exp->expanded_str);
		exp->new_split[2] = NULL;
	}
	//split function here
	free(exp->expanded_str);
	return (1);
}

char	**lets_expand(t_env **lst_env, char **split)
{
	t_exp	exp;

	exp.og_split = split;
	exp.index = -1;
	exp.new_split = malloc(sizeof(char *) * 3); //del
	exp.new_split[0] = ft_strdup(split[0]); //del
	while (exp.og_split[++exp.index])
	{
		exp.is_first = 1;
		if (exp.og_split[exp.index][0] == '$' && exp.og_split[exp.index][1] == '?' && !exp.og_split[exp.index][2])
			continue ;
		else if (exp.index > 0 && ft_strcmp(exp.og_split[exp.index - 1], "<<") == 0)
		{
			//exp.og_split[exp.index] = remove_quotes(exp.og_split[exp.index], exp.og_split);
			if (!exp.og_split[exp.index])
				handle_expand_error(lst_env);
			continue ;
		}
		if (!exp.expanded_str)
			return (NULL);
		if (!check_if_expand(lst_env, &exp, exp.og_split[exp.index], exp.index))
			printf("ke");
	}
	free_mem(exp.og_split);
	return (exp.new_split);
}