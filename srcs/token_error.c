/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:09:03 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/04 11:15:59 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error_token(void)
{
	ft_putstr_fd("error: unclosed quote\n", 2);
	return (1);
}

int	syntax_error_newline(void)
{
	ft_putstr_fd("Popcornshell: syntax error near unexpected token 'newline'\n", 2);
	return (2);
}

int	syntax_error_redir_token(t_token *token)
{
	if (token->type == APPEND)
		ft_putstr_fd("Popcornshell: syntax error near unexpected token '>>'\n", 2);
	else if (token->type == HEREDOC)
		ft_putstr_fd("Popcornshell: syntax error near unexpected token '<<'\n", 2);
	else if (token->type == REDIRIN)
		ft_putstr_fd("Popcornshell: syntax error near unexpected token '<'\n", 2);
	else if (token->type == REDIROUT)
		ft_putstr_fd("Popcornshell: syntax error near unexpected token '>'\n", 2);
	return (2);
}

int	syntax_error_pipe(void)
{
	ft_putstr_fd("Popcornshell: syntax error near unexpected token '|'\n", 2);
	return (2);
}

		
