#include "../../includes/expander.h"

/*static int	check_if_expand(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{

		}
	}
	return (0);
}*/
/*
static char	*remove_quotes(char *str)
{
	int	i;
	char	lead;

	//if (check_if_expand(str))
	//	is_expand = 1; //call a function to expand
	//i = -1;
	i = -1;
	if (str[0] == '"')
		lead = '"';
	else if (str[0] == '\'')
		lead = '\'';
	while (str[++i])
	{
		if (str[i] == '$')
	}
}

static void	handle_expander(t_word *word, t_operators *data)
{
	char	*new_comm;
	char	**new_flags;
	int		i;
	int		quote_counter;

	quote_counter = 0;
	i = -1;
	while (word->com[++i] == data->squote || word->com[i] == data->dquote)
		quote_counter++;
	new_comm = (char *)malloc(ft_strlen(word->com) - quote_counter + 1);
	if (!new_comm)
		printf("loll error\n");
	
	//comm
	//flags

}

void	expand_cli(t_word **word)
{
	t_word	*aux;

	aux = *word;
	while (aux)
	{
		if (aux->token == COMMAND)
			//expander
		aux = aux->next;
	}
}*/