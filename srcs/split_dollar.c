/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:17:38 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/07 11:39:50 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_for_dollar(char const *s, int *count)
{
	int	i;

	i = 0;
	if (s[i] == '$')
	{
		*count += 1;
		i++;
		if (s[i] >= '1' && s[i] <= '9')
			i++;
		else if (s[i] == '?')
			i++;
		else
		{
			while ((ft_isalnum(s[i]) || s[i] == '_') && s[i])
			{
				i++;
				if (s[i] == '$')
					break ;
			}
		}
	}
	return (i);
}

static int	ft_word_count(char const *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == '$')
			s += ft_count_for_dollar(s, &count);
		else if (*s != '\0')
		{
			count++;
			while (*s != '$' && *s)
				s++;
		}
	}
	return (count);
}

static int	ft_word_len(char const *s)
{
	int	i;
	int	wordlen;

	i = 0;
	wordlen = 0;
	if (*s == '$')
		wordlen += ft_count_for_dollar(s, &i);
	else
	{
		while (*s && *s != '$')
		{
			wordlen++;
			s++;
		}
	}
	return (wordlen);
}

char	**ft_dollar_malloc_tab(char const *s)
{
	char	**tab;

	tab = (char **)malloc(sizeof(*tab) * (ft_word_count(s) + 1));
	if (!tab)
		return (NULL);
	return (tab);
}

char	**ft_split_dollar(char const *s)
{
	char	**tab;
	int		i;
	int		index;

	if (s == 0)
		return (NULL);
	index = -1;
	i = 0;
	tab = ft_dollar_malloc_tab(s);
	if (!tab)
		return (NULL);
	while (++index < ft_word_count(s))
	{
		tab[index] = ft_strndup(s + i, ft_word_len(s + i));
		if (!tab[index])
			return (clean_tab(tab, index), NULL);
		i += ft_word_len(s + i);
	}
	tab[index] = NULL;
	return (tab);
}
