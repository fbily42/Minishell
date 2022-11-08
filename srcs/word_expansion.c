/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:01:49 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/08 11:32:18 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * char		*extract_word(t_token **token)
 * @token:	Token list
 * ||	Create a tab of all element of the token, expand if needed than return
 * ||	the expanded token word
 * ||	ex: [$COLORTERM" "$LESS] return [truecolor -R]
 *
 * int		we_create_word(char **tab, char **envp)
 * @tab:	
 * @envp:	Environment Variable
 *
 * char		*word_expansion(char **str)
 * @str:	Adress of a string
 * ||	Take a string and split it for every dollar sign inside.
 * ||	Use we_create_word() to replace the $variable by the correct output
 * ||	or empty string if no variable found
 * ||	Free the string @str
 * ||	After, recreate a string with the correct output and return it
 *
 * int	we_create_word(char **tab, char **envp)
 * @tab:	Tab of the split string (of the token)
 * @envp:	Environment of the shell
 * ||	Go throught the tab and replace all the $variable with the correct output
 * ||	return 1 if succes or 0 if allocation fail
 *
 * char	*we_reconstruct_word(char **tab, int index)
 * @tab:	Tab of the split string with $ replace
 * @index:	index (optimisation)
 * ||	Reconstruct a string from a tab
 */

extern int	g_minishell_exit;

// Delimiter	--> << HOME		|| Deli = HOME			|| gere avec l'option
// 				--> << HO$ME	|| deli = HO$ME			|| ""
// 				--> << $HOME	|| deli = $HOME			|| ""
// 				--> << $"HOME"	||	deli = HOME			|| 
// 				--> << $"HOME"$"HOME"	||	deli = HOMEHOME
// 				-->	<< $HOME"$HOME"		|| deli = $HOME$HOME

char	*extract_delimiter(t_token **token)
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
			ew_get_dquote(token, &tab[i], 0);
		else if (!itr_is_quote(get_tstr(token)))
			ew_get_word(token, &tab[i], 0);
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

char	*extract_word(t_token **token, int option)
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
			ew_get_word(token, &tab[i], option);
		else if (peek(get_tstr(token)) == '\"')
			ew_get_dquote(token, &tab[i], option);
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

int	we_create_word(char **tab, int i)
{
	char	*copy;
	int		tab_len;

	tab_len = tab_length(tab);
	while (tab[++i])
	{
		if (tab[i][0] == '$' && tab[i][1] == '?')
		{
			free(tab[i]);
			tab[i] = ft_itoa(g_minishell_exit);
		}
		else if (tab[i][0] == '$' && tab[i][1] != '\0')
		{
			copy = getenv(tab[i] + 1);
			free(tab[i]);
			if (copy == NULL)
				tab[i] = ft_strdup("");
			else
				tab[i] = ft_strdup(copy);
		}
		if (!tab[i])
			return (clean_tab(tab, tab_len), free(copy), 0);
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

char	*word_expansion(char **str)
{
	char	**tab;
	char	*result;

	tab = ft_split_dollar(*str);
	if (!tab)
		return (free(*str), NULL);
	if (!we_create_word(tab, -1))
		return (free(*str), NULL);
	result = we_reconstruct_word(tab, 0);
	if (!result)
		return (free(*str), NULL);
	free(*str);
	return (result);
}
