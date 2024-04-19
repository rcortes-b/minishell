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

static void	repair_redirect(t_word *lst_ptr)
{
	if (lst_ptr->com[0] == '<' || lst_ptr->com[0] == '>')
	{
		if (lst_ptr->in != -2)
		{
			close(lst_ptr->in);
			lst_ptr->in = -2;
		}
		if (lst_ptr->out != -2)
		{ 
			close(lst_ptr->out);
			lst_ptr->out = -2;
		}
	}
}

static void	update_node(t_word **lst, t_word **aux, int *is_redirect, t_word *lst_ptr)
{
	t_word *auxi; //del
	t_word	*tmp;
	int		is_head;

	repair_redirect(lst_ptr);
	auxi = *lst; //d
	printf("AUXI: %s LST: %p\n", auxi->next->com, *aux);
	while (auxi != *aux && auxi->next != *aux) {printf("AAA\n");
		auxi = auxi->next;}
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
	auxi->next = tmp;
	printf("vamo  %p\n", *lst);
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

static t_word	*open_redirect(t_word **lst, t_word *op, int check, t_env **my_env)
{
	if ((*lst)->in != -2 && check == 0)
		close((*lst)->in);
	else if ((*lst)->out != -2 && check == 1)
		close((*lst)->out);
	printf("lst_ptr: %s\n", (*lst)->com);
	if (op->token == REINPUT && !open_files(&(*lst)->in, op->next->com, 1))
			printf("File no se ha podido abrir.\n");
	else if (op->token == REOUTPUT)
	{
		if (!open_files(&(*lst)->out, op->next->com, 2))
			printf("File no se ha podido abrir.\n");
	}
	else if (op->token == HEREDOC)
	{
		if (!do_heredoc(lst, op->next->com, my_env))
			perror("KLK");
	}
	else if (op->token == APPEND_OPT)
	{
		if (!open_files(&(*lst)->out, op->next->com, 3))
			printf("File no se ha podido abrir.\n");
	}
	return (op);
}

t_word	**set_redirects(t_word **lst, t_operators *data, t_env **my_env)
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
			if (!open_redirect(&lst_ptr, aux, *aux->com == data->reoutput, my_env))
				return (NULL);
			update_node(lst, &aux, &is_redirect, lst_ptr);
			if (!*lst)
				return (NULL);
			continue ;
		}
		aux = aux->next;
	}
	if (is_redirect)
		lst_ptr->next = NULL;
	return (lst);
}