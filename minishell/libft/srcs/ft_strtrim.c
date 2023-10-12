/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:23:05 by sbeylot           #+#    #+#             */
/*   Updated: 2022/05/11 11:56:53 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Remove at the end and at the begining of the string the characters inside @set
 * Input --
 * @s1	: Source
 * @set	: Set of character to remove
 * Return --
 * string trim
 */

#include "../includes/libft.h"

static int	ft_ischarset(const char c, char const *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1_len;
	size_t	i;
	size_t	j;
	char	*ptr;

	s1_len = ft_strlen(s1) - 1;
	i = 0;
	j = 0;
	while (ft_ischarset(s1[i], set))
		i++;
	if (i == ft_strlen(s1))
	{
		ptr = ft_strdup("");
		return (ptr);
	}
	while (ft_ischarset(s1[s1_len], set) && s1_len != 0)
		s1_len--;
	ptr = (char *)malloc(sizeof(char) * (s1_len + 1 - i) + 1);
	if (ptr == NULL)
		return (NULL);
	while (i <= s1_len)
		ptr[j++] = s1[i++];
	ptr[j] = '\0';
	return (ptr);
}
