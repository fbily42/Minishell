/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:02:06 by sbeylot           #+#    #+#             */
/*   Updated: 2022/05/06 15:24:47 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Input --
 * @s : source
 * @c : character we are looking for
 * Return --
 * pointeur on the first occurance of c or NULL if c not found
 */

#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*result;
	int		i;

	i = 0;
	if (c == '\0')
	{
		result = (char *)s + ft_strlen(s);
		return (result);
	}
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
		{
			result = (char *)&s[i];
			return (result);
		}
		i++;
	}
	return (NULL);
}
