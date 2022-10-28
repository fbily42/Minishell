/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 15:22:39 by sbeylot           #+#    #+#             */
/*   Updated: 2022/08/17 17:25:35 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * trim @s with the charset
 * Input --
 * @s	: Source
 * @c	: char to trim with
 * Return
 * ptr with all strings from the function
 */

#include "../includes/libft.h"

static int	ft_word_count(char const *s, char *c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (ft_is_charset(*s, c) && *s)
			s++;
		if (*s != '\0')
			count++;
		while (!(ft_is_charset(*s, c)) && *s)
			s++;
	}
	return (count);
}

static int	ft_word_len(char const *s, char *c)
{
	int	wordlen;

	wordlen = 0;
	while (ft_is_charset(*s, c) && *s)
		s++;
	while (!(ft_is_charset(*s, c)) && *s)
	{
		wordlen++;
		s++;
	}
	return (wordlen);
}

static char	**ft_protection(char **tab, int index)
{
	int	i;

	i = 0;
	while (i < index && tab[i] != 0)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

static char	**ft_malloc_tab(char const *s, char *c)
{
	char	**tab;

	tab = (char **)malloc(sizeof(*tab) * (ft_word_count(s, c) + 1));
	if (!tab)
		return (NULL);
	return (tab);
}

char	**ft_split(char const *s, char *c)
{
	char	**tab;
	int		i;
	int		j;
	int		index;

	if (s == 0)
		return (0);
	index = -1;
	i = 0;
	tab = ft_malloc_tab(s, c);
	while (++index < ft_word_count(s, c))
	{
		j = 0;
		tab[index] = (char *)malloc(sizeof(char) * (ft_word_len(s + i, c) + 1));
		if (!tab[index])
			return (ft_protection(tab, index));
		while (s[i] && ft_is_charset(s[i], c))
			i++;
		while (s[i] && !(ft_is_charset(s[i], c)))
			tab[index][j++] = s[i++];
		tab[index][j] = '\0';
	}
	tab[index] = NULL;
	return (tab);
}
