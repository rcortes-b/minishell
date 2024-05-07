/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
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
#include "../../includes/expander.h"

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

static t_word	*update_node(t_word **lst, t_word **aux,
		int *is_redirect, t_word *lst_ptr)
{
	t_word	*auxi;
	t_word	*tmp;
	int		is_head;

	repair_redirect(lst_ptr);
	auxi = *lst;
	while (auxi != *aux && auxi->next != *aux)
		auxi = auxi->next;
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
	*is_redirect = 1;
	return (*lst);
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

static int	open_redir(t_word **lst, t_word *op,
	int check, t_env **my_env)
{
	if ((*lst)->in != -2 && check == 0)
		close((*lst)->in);
	else if ((*lst)->out != -2 && check == 1)
		close((*lst)->out);
	if (op->token == REINPUT && !open_files(&(*lst)->in, op->next->com, 1))
		return (perror("minishell"), g_errstatus = 1, 0);
	else if (op->token == REOUTPUT)
	{
		if (!open_files(&(*lst)->out, op->next->com, 2))
			return (perror("minishell"), g_errstatus = 1, 0);
	}
	else if (op->token == HEREDOC)
	{
		if (!do_heredoc(lst, op->next->com, my_env))//canviar el lst in o out a error
			return (g_errstatus = 1, 0);
	}
	else if (op->token == APPEND_OPT)
	{
		if (!open_files(&(*lst)->out, op->next->com, 3))
			return (perror("minishell"), g_errstatus = 1, 0);
	}
	return (1);
}

t_word	**set_redirects(t_word **lst, t_operators *data, t_env **env)
{
	t_word	*lst_ptr;
	t_word	*aux;
	int		is_redirect;
	int		head_com;
	int		is_delete;

	aux = *lst;
	lst_ptr = init_redirect_values(&is_delete, &head_com, &is_redirect);
	while (aux)
	{
		is_pipe(aux, &is_delete);
		set_redirect_values(&lst_ptr, &aux, &head_com, &is_redirect);
		if ((*aux->com == data->reinput || *aux->com == data->reoutput))
		{
			set_ambiguous_error(env, aux, &lst_ptr, &is_delete);
			if (!is_delete && !open_redir(&lst_ptr, aux, *aux->com == '>', env))
				is_delete = 1;
			if (!update_node(lst, &aux, &is_redirect, lst_ptr))
				return (NULL);
			continue ;
		}
		aux = aux->next;
	}
	set_redirect(is_redirect, &lst_ptr);
	return (lst);
}
