#include "../../includes/checker.h"

/*void	check_tokens(t_word **lst, t_operators *data)
{
	t_word	*aux;
	int		op_counter;

	if (is_symbol(data, (*lst)->com[0])) {
		printf("First is operator"); exit(EXIT_FAILURE);}//ret NULL, handle errpr
	aux = *lst;
	op_counter = 0;
	while (aux)
	{
		if (is_symbol(data, aux->com[0]))
		{
			if (op_counter == 1) {
				printf("double operator, cuidaoo\n"); exit(EXIT_FAILURE);}//handle error
			op_counter = 1;
		}
		else
			op_counter = 0;
		if (!aux->next && is_symbol(data, aux->com[0])) {
			printf("Last is operator, lel\n"); exit(EXIT_FAILURE);}//handle error
		aux = aux->next;
	}
}*/

void	check_tokens(char **words, t_operators *data)
{
	int	op_counter;
	int	i;

	if (words[0][0] == data->pipe || words[0][0] == data->reoutput) {
		printf("First is operator"); exit(EXIT_FAILURE);}//ret NULL, handle errpr
	op_counter = 0;
	i = -1;
	while (words[++i])
	{
		if (is_symbol(data, words[i][0]))
		{
			if (op_counter == 1) {
				printf("double operator, cuidaoo\n"); exit(EXIT_FAILURE);}//handle error
			op_counter = 1;
		}
		else
			op_counter = 0;
		if (!words[i + 1] && is_symbol(data, words[i][0])) {
			printf("Last is operator, lel\n"); exit(EXIT_FAILURE);}//handle error
	}
}