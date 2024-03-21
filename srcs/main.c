#include "../includes/parse.h"
#include "../includes/minishell.h"

static void	parse_main(t_word *words, char *line)
{
	t_operators	data;
	char		**split;

	init_data(&data);
	split = ft_split(line, " \t", &data);
	order_split(split, &data);
}

int main(void)
{
	t_word	words;

	words = NULL;
	char *line = readline("minishell> ");
	printf("Line: %s\n", line);
	char **spl = ft_split("ls -a > cat -b > mid -c > out -d", " \t");
	for (int i = 0; spl[i]; i++)
		printf("%s ", spl[i]);
	order_split(spl);
	printf("\n");
	for (int i = 0; spl[i]; i++)
		printf("%s ", spl[i]);
}