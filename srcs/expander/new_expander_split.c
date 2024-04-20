#include "../../includes/expander.h"
#include "../../includes/parse.h"
#include "../../includes/error.h"

static int	iterate_quotes(char const *str, size_t *index)
{
	char	c;

	if (str[*index] != '"' && str[*index] != '\'')
		return (0);
	c = str[*index];
	(*index)++;
	while (str[*index] && str[*index] != c)
		(*index)++;
	(*index)++;
	return (1);
}

static size_t	count_words(char const *str, char c)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	if (str[0] != c)
		counter++;
	while (str[i])
	{
		while (str[i] && str[i] != c )
		{
			if (str[i] == '\'' || str[i] == '"')
				iterate_quotes(str, &i);
			else
				i++;
		}
		if (str[i] == c)
			counter++;
		i++;
	}
	return (counter);
}

static int	next_word(char const *str, size_t *index, char c)
{
	size_t	size;
	char	lead;
	while (str[*index] && str[*index] == c)
		*index += 1;
	size = 0;
	lead = 'x';
	while (str[*index + size] && str[*index + size] != c)
	{
		if (str[*index + size] == '"' || str[*index + size] == '\'')
		{
			lead = str[*index + size];
			size++;
			while (str[*index + size] && str[*index + size] != lead)
				size++;
		}
		size++;
	}
	return (size);
}

static void	free_all(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	**expander_split(char const *s, char c)
{
	char	**strs;
	size_t	words;
	size_t	words_count;
	size_t	word_size;
	size_t	i;

	words = count_words(s, c);
	strs = ft_calloc(sizeof (char *), words + 1);
	if (!strs)
		return (NULL);
	i = 0;
	words_count = 0;
	while (words_count < words)
	{
		word_size = next_word(s, &i, c);
		strs[words_count] = ft_calloc(sizeof (char), word_size + 1);
		if (!strs[words_count])
		{
			free_all(strs);
			return (NULL);
		}
		ft_strlcpy(strs[words_count++], &s[i], word_size + 1);
		i += word_size;
	}
	return (strs);
}
