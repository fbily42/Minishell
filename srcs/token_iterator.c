/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_iterator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:05:01 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/15 09:21:44 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_next(char *itr)
{
	return (*itr != '\n' && *itr != '\0');
}

int	itr_is_redirection(char *c)
{
	if (is_symbol(c) == PIPE || is_symbol(c) == REDIRIN \
			|| is_symbol(c) == REDIROUT || is_symbol(c) == APPEND \
			|| is_symbol(c) == HEREDOC)
		return (1);
	return (0);
}

int	itr_is_quote(char *c)
{
	if (is_symbol(c) == SQUOTE || is_symbol(c) == DQUOTE)
		return (1);
	return (0);
}

char	peek(char *itr)
{
	return (*itr);
}

char	next(char **itr)
{
	char	next;

	next = **itr;
	*itr += 1;
	return (next);
}
