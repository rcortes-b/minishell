#include "../../includes/exec.h"
#include "../../includes/parse.h"
#include "../../includes/error.h"

static t_word	*open_redirect(t_word **lst, t_word *op)
{
	if ((*lst)->in != -2)
		close((*lst)->in);
	else if ((*lst)->out != -2)
		close((*lst)->out);
	if (op->token == REINPUT)
	{
		(*lst)->in = open(op->next->com, O_RDONLY);
		if ((*lst)->in == -1)
			perror("KLK");
	}
	else if (op->token == REOUTPUT)
	{
		(*lst)->out = open(op->next->com, O_CREAT | O_RDWR
				| O_TRUNC, 0644);
		if ((*lst)->out == -1)
			perror("KLK");
	}
	else if (op->token == HEREDOC)
	{
		if (!do_heredoc(lst, op->next->com))
			perror("KLK");
	}
	else if (op->token == APPEND_OPT)
	{
		(*lst)->out = open(op->next->com, O_CREAT | O_RDWR
				| O_APPEND, 0644);
		if ((*lst)->out == -1)
			perror("KLK");
	}
	return (op);
}

static t_word	**set_redirects(t_word **lst, t_operators *data)
{
	t_word	*lst_ptr;
	t_word	*aux;
	t_word	*tmp;
	int		is_redirect;
	int		head_com;

	aux = *lst;
	head_com = 1;
	is_redirect = 0;
	while (aux)
	{
		if (head_com == 1)
			lst_ptr = aux;
		head_com = 0;
		if (*aux->com == data->pipe)
		{
			head_com = 1;
			if (is_redirect)
				lst_ptr->next = aux;
			is_redirect = 0;
		}
		if (*aux->com == data->reinput || *aux->com == data->reoutput)
		{
			if (!open_redirect(&lst_ptr, aux))
				return (NULL);
			tmp = aux->next->next;
			free_word_node(&aux->next);
			free_word_node(&aux);
			aux = tmp;
			is_redirect = 1;
			continue ;
		}
		aux = aux->next;
	}
	if (is_redirect)
		lst_ptr->next = NULL;
	return (lst);
}

void	execution(t_word **lst, t_operators *data, t_env **my_env)
{
	//t_exec	*exe;
	lst = set_redirects(lst, data);
	if (!lst)
		return ;
	if (!cooking_execution(lst, my_env))
		return ;
}