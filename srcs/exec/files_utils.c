/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
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

int	ambiguos_redirect(t_env **env, t_word *aux)
{
	t_env	*tmp;

	if (*aux->com == '<' && aux->com[1] == '<')
		return (0);
	tmp = get_env(env, &aux->next->com[1]);
	if (!tmp || (tmp && tmp->only_exp))
		return (1);
	return (0);
}

t_word	*init_redirect_values(int *is_delete, int *head_com, int *is_redirect)
{
	*is_delete = 0;
	*head_com = 1;
	*is_redirect = 0;
	return (NULL);
}

void	set_ambiguous_error(t_env **env, t_word *aux,
		t_word **lst_ptr, int *is_delete)
{
	if (*aux->next->com == '$' && ambiguos_redirect(env, aux))
	{
		(*lst_ptr)->in = -1;
		(*lst_ptr)->out = -1;
		printf("minishell: %s: ambiguous redirect\n", aux->next->com);
		g_errstatus = 1;
		*is_delete = 1;
	}
}
