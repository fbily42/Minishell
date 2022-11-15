/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:09:13 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/15 09:21:12 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_token_type(int c)
{
	if (c == CMD)
		write(1, " (CMD)", 7);
	if (c == REDIR)
		write(1, " (REDIR)", 9);
	if (c == WORD)
		write(1, " (WORD)", 8);
	if (c == PIPE)
		write(1, " (PIPE)", 8);
	if (c == REDIRIN)
		write(1, " (REDIRIN)", 11);
	if (c == REDIROUT)
		write(1, " (REDIROUT)", 12);
	if (c == APPEND)
		write(1, " (APPEND)", 10);
	if (c == HEREDOC)
		write(1, " (HEREDOC)", 11);
	if (c == IONUMBER)
		write(1, " (IONUMBER)", 12);
	if (c == IOFILE)
		write(1, " (IOFILE)", 10);
	if (c == SQUOTE)
		write(1, " (SQUOTE)", 10);
	if (c == DQUOTE)
		write(1, " (DQUOTE)", 10);
}

void	token_print(t_token *token)
{
	if (!token)
		return ;
	while (token)
	{
		write(1, token->location.start, token->location.len);
		debug_token_type(token->type);
		printf(" Quote Nbr:%d, Elem Count: %d, Len: %d\n", token->location.qnbr, \
				token->location.elem, token->location.len);
		token = token->next;
	}
}

char	*debug_node_type(int c)
{
	if (c == CMD)
		return ("CMD");
	if (c == REDIR)
		return ("REDIR");
	if (c == PIPE)
		return ("PIPE");
	if (c == REDIRIN)
		return ("REDIRIN");
	if (c == REDIROUT)
		return ("REDIROUT");
	if (c == APPEND)
		return ("APPEND");
	if (c == HEREDOC)
		return ("HEREDOC");
	return (NULL);
}
