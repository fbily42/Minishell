/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:15:36 by sbeylot           #+#    #+#             */
/*   Updated: 2022/05/10 19:19:54 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Compare s1 with s2 to max bytes
 * Input --
 * @s1	: String 1
 * @s2	: String 2
 * @n	: Maximum bytes to scan
 * Return --
 * return a negative int if s1 < s2, 0 if s1 == s2, a positive int if s1 > s2
 */

#include "../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*ptr_s1;
	unsigned char	*ptr_s2;

	ptr_s1 = (unsigned char *)s1;
	ptr_s2 = (unsigned char *)s2;
	while (n--)
	{
		if (*ptr_s1 != *ptr_s2)
			return (*ptr_s1 - *ptr_s2);
		ptr_s1++;
		ptr_s2++;
	}
	return (0);
}
