/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_iterator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:05:01 by sbeylot           #+#    #+#             */
/*   Updated: 2022/10/25 16:03:32 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * int	has_next(char *itr)
 * @itr:	Pointer on the current char
 * ||	Check if the current char is the end of the input
 *
 * int	itr_is_redirection(char *c)
 * @c:		Pointer on the current char
 * ||	Check if the current char is a redirection char
 *
 * int	itr_is_quote(char *c)
 * @c:		Pointer on the current char
 * ||	Check if the current char is a quoted char
 *
 * char	peek(char *itr)
 * @itr		Pointer on the current char
 * ||	Return the current char
 *
 * char	next(char **itr)
 * @itr:	Adress of the pointeur on the current char
 * ||	Move to the next char and return the next char (if needed)
 */

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
