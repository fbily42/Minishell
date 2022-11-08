/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:15:26 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/08 11:24:29 by sbeylot          ###   ########.fr       */
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

char	*ew_get_word(t_token **token, char **str, int option)
{
	char	*pstr;

	pstr = (*token)->location.start;
	*str = ft_strndup(get_tstr(token), add_word_len(&pstr));
	if (!str)
		return (NULL);
	add_word_len(&(*token)->location.start);
	if (dollar_inside(*str) >= 0 && option)
		*str = word_expansion(str);
	return (*str);
}

char	*ew_get_dquote(t_token **token, char **str, int option)
{
	char	*pstr;

	pstr = (*token)->location.start;
	if (option != 0)
		*str = ft_strndup(get_tstr(token) + 1, add_quoted_len(&pstr, \
				is_symbol(get_tstr(token))) - 2);
	else
	{
		pstr += 1;
		*str = ft_strndup(get_tstr(token) + 2, \
				add_quoted_len(&pstr, DQUOTE) - 2);
	}
	if (!str)
		return (NULL);
	if (option != 0)
		add_quoted_len(&(*token)->location.start, is_symbol(get_tstr(token)));
	else
	{
		(*token)->location.start += 1;
		add_quoted_len(&(*token)->location.start, DQUOTE);
		(*token)->location.elem -= 1;
	}
	if (dollar_inside(*str) >= 0 && option)
		*str = word_expansion(str);
	return (*str);
}

char	*ew_get_squote(t_token **token, char **str)
{
	char	*pstr;

	pstr = (*token)->location.start;
	*str = ft_strndup(get_tstr(token) + 1, \
			add_quoted_len(&pstr, \
			is_symbol(get_tstr(token))) - 2);
	if (!str)
		return (NULL);
	add_quoted_len(&(*token)->location.start, is_symbol(get_tstr(token)));
	return (*str);
}
