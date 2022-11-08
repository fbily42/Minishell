/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 12:13:38 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/08 11:20:38 by sbeylot          ###   ########.fr       */
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

t_token	*init_token(char **itr, t_type type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->next = NULL;
	token->location = (t_slice){.start = *itr, .len = 0, .qnbr = 0, .elem = 0};
	return (token);
}
