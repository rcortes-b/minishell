/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcortes- <rcortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:05:57 by rcortes-          #+#    #+#             */
/*   Updated: 2024/03/21 18:23:59 by mvallhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

enum tokenization
{
	COMMAND,
	PIPE,  // | 
	SQUOTE, // '  '
	DQUOTE, // " "
	REINPUT, // <
	REOUTPUT, // >
	HEREDOC, // <<
	APPEND_OPT // >>
};

#endif
