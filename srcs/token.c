/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:03:15 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/12 13:57:50 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
 * t_token:
 * @type:		Token type
 * @location:	Information of the token
 *
 * t_slice:
 * @start:		Pointer on the beginning of the token 
 * @len:		Token length
 * @qnbr:		Number of quoted elements (optionnal) 
 * @elem:		Number of element in the token (ex:Minishell$PATHok$LESS == 4)
 *
 * int		add_token(t_token **tokens, t_token *token)
 * @tokens:		Token list
 * @token:		New token
 * || Add a new token in the list
 *
 * t_token	*token_symbol(char **itr)
 * @itr:		Pointer on the beginning of the token
 * ||	Token creation depending of a symbol (ex: < > | etc...)
 *
 * void		tokenizer(char *line, t_token **token)
 * @line:		User Input	
 * @token:		Token List
 * ||	Token list creation
 */

static int	token_var_exist(char *str, char **envp, int len)
{
	int	i;

	i = -1;
	if (!*envp)
		return (0);
	if (ft_strncmp(str, "$?", 2) == 0)
		return (1);
	if (str[0] == '$' && str[1] == '\0')
		return (1);
	len--;
	str++;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], str, len) == 0)
			return (1);
	}
	return (0);
}

int	is_single_dollar(t_token *token)
{
	char	*ptr;

	if (!token)
		return (0);
	ptr = token->location.start;
	if (peek(ptr) == '$')
	{
		next(&ptr);
		if (itr_is_quote(ptr))
			return (0);
		while (has_next(ptr) && !is_whitespace(*ptr))
		{
			if (peek(ptr) == '$')
				return (0);
			if (itr_is_quote(ptr))
				return (0);
			next(&ptr);
		}
		return (1);
	}
	return (0);
}

int	add_token(t_token **tokens, t_token *token, t_context *ctx)
{
	t_token	*cur;

	if (token == NULL)
		return (0);
	if (is_single_dollar(token) && \
			!token_var_exist(token->location.start, ctx->envp, \
				var_len(token->location.start)))
		return (free(token), 1);
	if (*tokens == NULL)
		*tokens = token;
	else
	{
		cur = *tokens;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = token;
	}
	return (1);
}

t_token	*token_symbol(char **itr)
{
	t_token	*token;

	token = NULL;
	if ((is_symbol(*itr) == SQUOTE || is_symbol(*itr) == DQUOTE) \
			&& !is_closed(*itr, peek(*itr)))
		return (0);
	if (is_symbol(*itr) == SQUOTE || is_symbol(*itr) == DQUOTE)
		token = token_quoted(itr);
	else if (is_symbol(*itr) == APPEND || is_symbol(*itr) == HEREDOC)
		token = token_redir2(itr);
	else if (is_symbol(*itr) == REDIRIN || is_symbol(*itr) == REDIROUT)
		token = token_redir(itr);
	else if (is_symbol(*itr) == PIPE)
	{
		token = token_single_symbol(itr);
		if (!has_next(*itr))
			return (syntax_error_pipe(), NULL);
	}
	if (!token)
		return (NULL);
	return (token);
}

void	tokenizer(char *line, t_token **tokens, t_context *ctx)
{
	char	*itr;

	itr = line;
	if (is_symbol(itr) == PIPE)
	{
		syntax_error_pipe();
		return ;
	}
	while (has_next(itr))
	{
		if (is_whitespace(peek(itr)))
			next(&itr);
		else if (peek(itr) == '$' && itr_is_quote(itr + 1))
			next(&itr);
		else if (is_symbol(itr))
		{
			if (add_token(tokens, token_symbol(&itr), ctx) == 0)
				return (free_token(tokens));
		}
		else
		{
			if (add_token(tokens, token_word(&itr), ctx) == 0)
				return (free_token(tokens));
		}
	}
}
