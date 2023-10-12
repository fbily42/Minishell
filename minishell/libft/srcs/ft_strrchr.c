/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:09:54 by sbeylot           #+#    #+#             */
/*   Updated: 2022/05/11 09:54:41 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Input --
 * @s : source
 * @c : character we are looking for
 * Return --
 * pointeur on the last occurance of c or NULL if c not found
 */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*result;
	int		i;

	i = ft_strlen(s);
	if (c == '\0')
	{
		result = (char *)&s[i];
		return (result);
	}
	else
		i--;
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
		{
			result = (char *)&s[i];
			return (result);
		}
		i--;
	}
	return (NULL);
}
