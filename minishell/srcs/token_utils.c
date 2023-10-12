/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:04:06 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/15 09:21:23 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
