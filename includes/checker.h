/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:22:16 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/26 17:22:17 by rcortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "minishell.h"
# include "parse.h"

//void	check_tokens(t_word **lst, t_operators *data);
void	check_tokens(char **words, t_operators *data);

#endif
