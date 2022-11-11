/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:04:06 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/11 12:32:52 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * int	is_whitespace(char c)
 * @c:	Current char
 * ||	Is the char a whitespace
 * ||	1 == yes
 * ||	0 == no
 *
 * int	is_ignored(char c)
 * @c:	Current char
 * ||	Do we need to ignore those char
 * ||	1 == yes
 * ||	0 == No
 *
 * int	is_symbol(char *c)
 * @c:	Pointer on the current char
 * ||	Return the symbol type of the char for the token.type
 *
 * int	is_closed(char *itr, char quote)
 * @itr:	Pointer on the current char
 * @quote:	Quote type (" or ')
 * ||	Check if the quote is close
 * ||	1 == yes
 * ||	0 == no
 *
 * void	free_token(t_token **token)
 * ||	Free token list
 */

int	is_whitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	is_ignored(char c)
{
	return (c == '\\' && c == ';');
}

int	is_symbol(char *c)
{
	if (peek(c) == '|')
		return (PIPE);
	else if (peek(c) == '<' && peek(c + 1) == '<')
		return (HEREDOC);
	else if (peek(c) == '>' && peek(c + 1) == '>')
		return (APPEND);
	else if ((ft_isdigit(peek(c)) && peek(c + 1) == '<') || peek(c) == '<')
		return (REDIRIN);
	else if ((ft_isdigit(peek(c)) && peek(c + 1) == '>') || peek(c) == '>')
		return (REDIROUT);
	else if (peek(c) == '\'')
		return (SQUOTE);
	else if (peek(c) == '\"')
		return (DQUOTE);
	return (0);
}

int	is_closed(char *itr, char quote)
{
	char	*temp;

	temp = itr;
	next(&temp);
	while (has_next(temp))
	{
		if (peek(temp) == quote)
			return (1);
		next(&temp);
	}
	print_error_token();
	return (0);
}

void	free_token(t_token **token)
{
	t_token	*temp;

	if (*token == NULL)
		return ;
	while (*token)
	{
		temp = (*token)->next;
		free(*token);
		*token = temp;
	}
}
