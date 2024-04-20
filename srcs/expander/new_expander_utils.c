
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
	while (str[i + *j] && str[i + *j] != '$'
		&& str[i + *j] != '"' && str[i + *j] != '\'' && str[i + *j] != ' ')
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
