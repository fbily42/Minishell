/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 12:27:43 by sbeylot           #+#    #+#             */
/*   Updated: 2022/05/03 13:54:43 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Input --
 * @dest	:	destination
 * @src		:	source
 * @n		:	Nombre de bytes a copier
 * Return --
 * pointer to dest
 */

#include "../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*ptr_d;
	const unsigned char	*ptr_s;
	unsigned char		*last_d;
	const unsigned char	*last_s;

	ptr_d = dest;
	ptr_s = src;
	if (ptr_d < ptr_s)
	{
		while (n--)
			*ptr_d++ = *ptr_s++;
	}
	else
	{
		last_d = dest + (n - 1);
		last_s = src + (n - 1);
		while (n--)
			*last_d-- = *last_s--;
	}
	return (dest);
}
