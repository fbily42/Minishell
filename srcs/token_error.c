/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:09:03 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/15 16:53:48 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_minishell_exit;

int	print_error_token(void)
{
	ft_putstr_fd("PopCornShell: syntax error, unclosed quote\n", 2);
	g_minishell_exit = 2;
	return (1);
}

int	syntax_error_newline(void)
{
	ft_putstr_fd("PopCornShell: syntax error near unexpected token 'newline'\n"\
		, 2);
	g_minishell_exit = 2;
	return (2);
}

int	syntax_error_redir_token(t_token *token)
{
	if (token->type == APPEND)
		ft_putstr_fd("PopCornShell: syntax error near unexpected token '>>'\n" \
			, 2);
	else if (token->type == HEREDOC)
		ft_putstr_fd("PopCornShell: syntax error near unexpected token '<<'\n" \
			, 2);
	else if (token->type == REDIRIN)
		ft_putstr_fd("PopCornShell: syntax error near unexpected token '<'\n" \
			, 2);
	else if (token->type == REDIROUT)
		ft_putstr_fd("PopCornShell: syntax error near unexpected token '>'\n" \
			, 2);
	g_minishell_exit = 2;
	return (2);
}

int	syntax_error_pipe(void)
{
	ft_putstr_fd("PopcornShell: syntax error near \
		unexpected token '|'\n", 2);
	g_minishell_exit = 2;
	return (2);
}

int	error_token(t_token **token, char **itr)
{
	if (!has_next(*itr))
		return (syntax_error_newline());
	if (is_symbol(*itr) == PIPE)
		return (free(*token), syntax_error_pipe());
	if (itr_is_redirection(*itr))
		return (syntax_error_redir_token(*token), free(*token), 2);
	return (0);
}
