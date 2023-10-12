/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:55:50 by sbeylot           #+#    #+#             */
/*   Updated: 2022/05/10 18:43:36 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Find the first occurence of c in s
 * Input --
 * @s	: source
 * @c	: character to find
 * @n	: Maximum bytes to scan
 * Return --
 * return a pointer to first c in s
 */

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr_s;
	size_t			i;

	ptr_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*ptr_s == (unsigned char)c)
			return (ptr_s);
		ptr_s++;
		i++;
	}
	return (NULL);
}
