/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 09:45:16 by sbeylot           #+#    #+#             */
/*   Updated: 2022/10/24 09:45:41 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/* --- Old Function --- */

char	*extract_word(t_token **token)
{
	char	*str;

	if (get_ttype(token) == WORD)
		str = ft_strndup(get_tstr(token), get_tlen(token));
	else
		str = ft_strndup(get_tstr(token) + 1, get_tlen(token) - 2);
	if (!str)
		return (NULL);
	if (dollar_inside(str) >= 0 && get_ttype(token) != SQUOTE)
	{
		str = word_expansion(&str);
	}	
	eat_token(token);
	return (str);
}
