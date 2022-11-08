/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:10:31 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/08 11:19:31 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * t_token		*token_word(char **itr)
 * @itr:		Pointer on the beginning of the token 
 * ||	Token creation of WORD type 
 * 
 * t_token		*token_single_symbol(char **itr)
 * @itr:		Pointer on the beginning of the token 
 * ||	Token creation of type < > |
 *
 * t_token		*token_quoted(char **itr)
 * @itr:		Pointer on the beginning of the token 
 * ||	Token Creation of type "" or '' if itr == ' or "
 *
 * t_token		*token_append_heredoc(char **itr)
 * @itr:		Pointer on the beginning of the token 
 * ||	Token Creation of type << >>
 */

t_token	*token_word(char **itr)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = WORD;
	token->next = NULL;
	token->location = (t_slice){.start = *itr, .len = 0, .qnbr = 0, .elem = 0};
	while (has_next(*itr) && !is_whitespace(peek(*itr)))
	{
		if (itr_is_redirection(*itr))
			return (token);
		token->location.len += add_word_len(itr);
		token->location.elem += 1;
		if (itr_is_quote(*itr) && !is_closed(*itr, peek(*itr)))
			return (free(token), NULL);
		while (itr_is_quote(*itr) && is_closed(*itr, peek(*itr)))
		{
			token->location.len += add_quoted_len(itr, is_symbol(*itr));
			token->location.qnbr += 1;
			token->location.elem += 1;
		}
	}
	return (token);
}

t_token	*token_delim(char **itr)
{
	t_token	*token;

	token = init_token(itr, WORD);
	if (!token)
		return (NULL);
	while (has_next(*itr) && !is_whitespace(peek(*itr)))
	{
		if (peek(*itr) == '$' && peek(*itr + 1) == '\"')
			next(itr);
		if (itr_is_redirection(*itr))
			return (token);
		token->location.len += add_word_len(itr);
		token->location.elem += 1;
		if (itr_is_quote(*itr) && !is_closed(*itr, peek(*itr)))
			return (free(token), NULL);
		while (itr_is_quote(*itr) && is_closed(*itr, peek(*itr)))
		{
			token->location.len += add_quoted_len(itr, is_symbol(*itr));
			token->location.qnbr += 1;
			token->location.elem += 1;
		}
	}
	return (token);
}

t_token	*token_single_symbol(char **itr)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = is_symbol(*itr);
	token->location = (t_slice){.start = *itr, .len = 1, .qnbr = 0, .elem = 1};
	token->next = NULL;
	next(itr);
	return (token);
}

t_token	*token_quoted(char **itr)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = WORD;
	token->location = (t_slice){.start = *itr, .len = 1, .qnbr = 0, .elem = 0};
	while (has_next(*itr) && !is_whitespace(peek(*itr)))
	{
		if (itr_is_quote(*itr) && !is_closed(*itr, peek(*itr)))
			return (free(token), NULL);
		if (itr_is_quote(*itr))
		{
			token->location.len += add_quoted_len(itr, is_symbol(*itr));
			token->location.qnbr += 1;
			token->location.elem += 1;
		}
		else
		{
			token->location.len += add_word_len(itr);
			token->location.elem += 1;
		}
	}
	token->next = NULL;
	return (token);
}

t_token	*token_append_heredoc(char **itr)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = is_symbol(*itr);
	token->location = (t_slice){.start = *itr, .len = 2, .qnbr = 0, .elem = 1};
	next(itr);
	next(itr);
	token->next = NULL;
	return (token);
}
