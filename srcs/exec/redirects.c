/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:28:06 by rcortes-          #+#    #+#             */
/*   Updated: 2024/04/11 11:28:07 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/parse.h"
#include "../../includes/error.h"

void	set_redirect_values(t_word **lst_ptr, t_word **aux,
	int *head_com, int *is_redirect)
{
	if (*head_com == 1)
		*lst_ptr = *aux;
	*head_com = 0;
	if (*(*aux)->com == '|')
	{
		*head_com = 1;
		if (*is_redirect)
			(*lst_ptr)->next = *aux;
		*is_redirect = 0;
	}
}

void	update_node(t_word **lst, t_word **aux, int *is_redirect)
{
	t_word	*tmp;
	int		is_head;

	is_head = 0;
	if (*lst == *aux)
		is_head = 1;
	tmp = (*aux)->next->next;
	free_word_node(&(*aux)->next);
	free_word_node(aux);
	if (is_head == 1)
	{
		*aux = tmp;
		*lst = *aux;
	}
	else
		*aux = tmp;
	*is_redirect = 1;
}

static int	open_files(int *fd, char *file, int flag_type)
{
	if (flag_type == 1)
		*fd = open(file, O_RDONLY);
	else if (flag_type == 2)
		*fd = open(file, O_CREAT | O_RDWR
				| O_TRUNC, 0644);
	else if (flag_type == 3)
		*fd = open(file, O_CREAT | O_RDWR
				| O_APPEND, 0644);
	if (*fd == -1)
		return (0);
	return (1);
}

static t_word	*open_redirect(t_word **lst, t_word *op, int check)
{
	if ((*lst)->in != -2 && check == 0)
		close((*lst)->in);
	else if ((*lst)->out != -2 && check == 1)
		close((*lst)->out);
	if (op->token == REINPUT && !open_files(&(*lst)->in, op->next->com, 1))
			printf("File no se ha podido abrir.\n");
	else if (op->token == REOUTPUT)
	{
		if (!open_files(&(*lst)->out, op->next->com, 2))
			printf("File no se ha podido abrir.\n");
	}
	else if (op->token == HEREDOC)
	{
		if (!do_heredoc(lst, op->next->com))
			perror("KLK");
	}
	else if (op->token == APPEND_OPT)
	{
		if (!open_files(&(*lst)->out, op->next->com, 3))
			printf("File no se ha podido abrir.\n");
	}
	return (op);
}

t_word	**set_redirects(t_word **lst, t_operators *data)
{
	t_word	*lst_ptr;
	t_word	*aux;
	int		is_redirect;
	int		head_com;

	aux = *lst;
	head_com = 1;
	is_redirect = 0;
	lst_ptr = NULL;
	while (aux)
	{
		set_redirect_values(&lst_ptr, &aux, &head_com, &is_redirect);
		if (*aux->com == data->reinput || *aux->com == data->reoutput)
		{
			//printf("%p   %p\n\n", *lst, aux);
			if (!open_redirect(&lst_ptr, aux, *aux->com == data->reoutput))
				return (NULL);
			update_node(lst, &aux, &is_redirect);
			printf("%p   %p\n\n", *lst, aux);
			//printf("\n");
			continue ;
		}
		aux = aux->next;
	}
	if (is_redirect)
		lst_ptr->next = NULL;
	fprintf(stderr, "IN: %d\nOUT: %d\n", (*lst)->in, (*lst)->out); // gestion de errores
	return (lst);
}

//Esto lo cambio por set_redirect_values//

/*if (head_com == 1)
	lst_ptr = aux;
head_com = 0;
if (*aux->com == data->pipe)
{
	head_com = 1;
	if (is_redirect)
		lst_ptr->next = aux;
	is_redirect = 0;
}*/

//Esto lo cambio por update node//

/*
tmp = aux->next->next;
free_word_node(&aux->next);
free_word_node(&aux);
aux = tmp;
is_redirect = 1;
*/
