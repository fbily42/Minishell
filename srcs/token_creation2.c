/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creation2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:13:53 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/08 11:29:39 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * t_token		*token_redir(char **itr) && token_redir_fd(char **itr)
 * @itr:		Pointer on the beginning of the token 
 * || token_redir =		Token Creation of redirection type 
 * || token_redir_fd =	Token Creation of redirection type with fd
 *
 * t_token		*token_redir2(char **itr) && token_redir2_fd(char **itr)
 * @itr:		Pointer on the beginning of the token 
 * || token_redir2 =		Token Creation of redirection type 
 * || token_redir2_fd =		Token Creation of redirection type with fd
 *
 */

//Error [ < ] [ > ] [ << ] [ >> ] 

t_token	*token_redir_fd(char **itr)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = IONUMBER;
	token->location = (t_slice){.start = *itr, .len = 1, .qnbr = 0, .elem = 1};
	next(itr);
	token->next = token_single_symbol(itr);
	if (!token->next)
		return (free(token), NULL);
	while (has_next(*itr) && is_whitespace(peek(*itr)))
		next(itr);
	if (!has_next(*itr))
		return (syntax_error_newline(), NULL);
	if (itr_is_quote(*itr))
		token->next->next = token_quoted(itr);
	else
		token->next->next = token_word(itr);
	if (!token->next->next)
		return (free(token->next), free(token), NULL);
	token->next->next->type = IOFILE;
	return (token);
}

t_token	*token_redir2_fd(char **itr)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = IONUMBER;
	token->location = (t_slice){.start = *itr, .len = 1, .qnbr = 0, .elem = 1};
	next(itr);
	token->next = token_append_heredoc(itr);
	if (!token->next)
		return (free(token), NULL);
	while (has_next(*itr) && is_whitespace(peek(*itr)))
		next(itr);
	if (error_token(&token, itr))
		return (NULL);
	if (itr_is_quote(*itr))
		token->next->next = token_quoted(itr);
	else
		token->next->next = token_word(itr);
	if (!token->next->next)
		return (free(token->next), free(token), NULL);
	token->next->next->type = IOFILE;
	return (token);
}

t_token	*token_redir(char **itr)
{
	t_token	*token;

	if (ft_isalnum(peek(*itr)))
		token = token_redir_fd(itr);
	else
	{
		token = token_single_symbol(itr);
		if (!token)
			return (NULL);
		while (has_next(*itr) && is_whitespace(peek(*itr)))
			next(itr);
		if (error_token(&token, itr))
			return (NULL);
		if (itr_is_quote(*itr))
			token->next = token_quoted(itr);
		else
			token->next = token_word(itr);
		if (!token->next)
			return (free(token), NULL);
		token->next->type = IOFILE;
	}
	if (!token)
		return (NULL);
	return (token);
}

t_token	*token_redir2(char **itr)
{
	t_token	*token;

	if (ft_isalnum(peek(*itr)))
		token = token_redir2_fd(itr);
	else
	{
		token = token_append_heredoc(itr);
		while (has_next(*itr) && is_whitespace(peek(*itr)))
			next(itr);
		if (!token || error_token(&token, itr))
			return (NULL);
		if (itr_is_quote(*itr))
			token->next = token_quoted(itr);
		else if (token->type == HEREDOC)
			token->next = token_delim(itr);
		else
			token->next = token_word(itr);
		if (!token->next)
			return (free(token), NULL);
		token->next->type = IOFILE;
	}
	if (!token)
		return (NULL);
	return (token);
}
