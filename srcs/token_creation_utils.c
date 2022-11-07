/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:13:38 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/07 14:40:42 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * int	add_quoted_len(char **itr, t_type type)
 * @itr:		Pointer on the beginning of the token 
 * @type:		Token type
 * ||	Length of a quoted element
 *
 * int	add_word_len(char **itr)
 * @itr:		Pointer on the beginning of the token 
 * @type:		Token type
 * ||	Length of a word element
 * Those functions increment the len of the token 
 * (token.location.len)
 */

int	add_quoted_len(char **itr, t_type type)
{
	int	i;

	i = 1;
	/*
	if (peek(*itr) == '$')
		next(itr);
	*/
	next(itr);
	while (is_symbol(*itr) != (int)type)
	{
		i++;
		next(itr);
	}
	i++;
	next(itr);
	return (i);
}

int	add_word_len(char **itr)
{
	int	i;

	i = 0;
	while (has_next(*itr) && !is_whitespace(peek(*itr)))
	{
		if (itr_is_redirection(*itr))
			break ;
		if (itr_is_quote(*itr))
			break ;
		i++;
		next(itr);
	}
	return (i);
}
