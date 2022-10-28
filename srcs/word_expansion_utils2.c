/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:15:26 by sbeylot           #+#    #+#             */
/*   Updated: 2022/10/26 09:54:23 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	char	*ew_get_word(t_token **token, char **str)
 *	@token:		Token list
 *	@str:		Adress of the string
 *	||		If the token is a WORD, return the correct string from it
 *
 *	char	*ew_get_dquote(t_token **token, char **str)
 *	@token:		Token List
 *	@str:		Adress of a string
 *	||  	If the token is a DQUOTE, return the correct string from it
 *
 *	char	*ew_get_squote(t_token **token, char **str)
 *	@token:		Token List
 *	@str:		Adress of a string
 *	||  	If the token is a SQUOTE, return the correct string from it

 */

char	*ew_get_word(t_token **token, char **str)
{
	*str = ft_strndup(get_tstr(token), add_word_len(&(*token)->location.start));
	if (!str)
		return (NULL);
	if (dollar_inside(*str) >= 0)
		*str = word_expansion(str);
	return (*str);
}

char	*ew_get_dquote(t_token **token, char **str)
{
	*str = ft_strndup(get_tstr(token) + 1, \
			add_quoted_len(&(*token)->location.start, \
			is_symbol(get_tstr(token))) - 2);
	if (!str)
		return (NULL);
	if (dollar_inside(*str) >= 0)
		*str = word_expansion(str);
	return (*str);
}

char	*ew_get_squote(t_token **token, char **str)
{
	*str = ft_strndup(get_tstr(token) + 1, \
			add_quoted_len(&(*token)->location.start, \
			is_symbol(get_tstr(token))) - 2);
	if (!str)
		return (NULL);
	return (*str);
}
