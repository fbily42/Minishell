/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:01:49 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/15 09:22:09 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_minishell_exit;

char	*extract_delimiter(t_token **token, t_context *ctx)
{
	char	**tab;
	char	*str;
	int		i;

	i = -1;
	tab = (char **)malloc(sizeof(char *) * ((*token)->location.elem + 1));
	if (!tab)
		return (NULL);
	while (++i < (*token)->location.elem)
	{
		if (peek(get_tstr(token)) == '$' && peek((*token)->location.start + 1) \
				== '\"')
			ew_get_dquote(token, &tab[i], 0, ctx);
		else if (!itr_is_quote(get_tstr(token)))
			ew_get_word(token, &tab[i], 0, ctx);
		else if (itr_is_quote(get_tstr(token)))
			ew_get_squote(token, &tab[i]);
	}
	tab[i] = NULL;
	str = we_reconstruct_word(tab, 0);
	if (!str)
		return (NULL);
	eat_token(token);
	return (str);
}

char	*extract_word(t_token **token, int option, t_context *ctx)
{
	char	**tab;
	char	*str;
	int		i;

	i = -1;
	tab = (char **)malloc(sizeof(char *) * ((*token)->location.elem + 1));
	if (!tab)
		return (NULL);
	while (++i < (*token)->location.elem)
	{
		if (!itr_is_quote(get_tstr(token)))
			ew_get_word(token, &tab[i], option, ctx);
		else if (peek(get_tstr(token)) == '\"')
			ew_get_dquote(token, &tab[i], option, ctx);
		else
			ew_get_squote(token, &tab[i]);
		if (!tab[i])
			return (clean_tab(tab, i), NULL);
	}
	tab[i] = NULL;
	str = we_reconstruct_word(tab, 0);
	if (!str)
		return (NULL);
	eat_token(token);
	return (str);
}

int	we_create_word(char **tab, int i, t_context *ctx)
{
	int		tab_len;

	tab_len = tab_length(tab);
	while (tab[++i])
	{
		we_create_word_utils(tab, i, ctx, tab_len);
		if (!tab[i])
			return (clean_tab(tab, tab_len), 0);
	}
	return (1);
}

char	*we_reconstruct_word(char **tab, int index)
{
	int		i;
	int		j;
	char	*word;
	int		tab_len;

	index = -1;
	j = 0;
	tab_len = tab_length(tab);
	word = (char *)malloc(sizeof(char) * word_expansion_len(tab) + 1);
	if (!word)
		return (clean_tab(tab, tab_len), NULL);
	while (tab[++index])
	{
		i = 0;
		while (tab[index][i])
			word[j++] = tab[index][i++];
	}
	word[j] = '\0';
	clean_tab(tab, index);
	return (word);
}

char	*word_expansion(char **str, t_context *ctx)
{
	char	**tab;
	char	*result;

	tab = ft_split_dollar(*str);
	if (!tab)
		return (free(*str), NULL);
	if (!we_create_word(tab, -1, ctx))
		return (free(*str), NULL);
	result = we_reconstruct_word(tab, 0);
	if (!result)
		return (free(*str), NULL);
	free(*str);
	return (result);
}
