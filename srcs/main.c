#include "../includes/parse.h"
#include "../includes/minishell.h"

//char **spl = ft_split("ls -a > cat -b > mid -c > out -d", " \t");

static void	parse_main(t_word *words, char *line)
{
	t_operators	data;
	char		**split;

	init_data(&data);
	printf("Line: %s\n", line);
	printf("\n");
	split = ft_split(line, " \t", &data);
	for (int i = 0; split[i]; i++)
		printf("%s ", split[i]);
	printf("\n");
	order_split(split, &data);
	for (int i = 0; split[i]; i++)
		printf("%s ", split[i]);
	printf("\n");

	categorize(split, &words, &data);
	while (words)
	{
		int	i = -1;
		printf("com: %s\n", words->com);
		printf("flags:\n");
		while (words->flags[++i])
			printf("  - %s\n", words->flags[i]);
	}
}

int main(void)
{
	t_word	*words;
	char *line;

	words = NULL;
	line = readline("minishell> ");
	parse_main(words, line);
}
