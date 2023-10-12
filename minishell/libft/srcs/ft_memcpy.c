/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 11:53:58 by sbeylot           #+#    #+#             */
/*   Updated: 2022/05/03 13:49:36 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Input --
 * @dest	:	destionation
 * @src		:	source
 * @n		:	bytes to copy
 * Return --
 * pointer to dest
 */

#include "../includes/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*ptr_dest;
	const char	*ptr_src;

	ptr_dest = (char *)dest;
	ptr_src = (const char *)src;
	if (ptr_dest != NULL && ptr_src != NULL)
	{
		while (n--)
			*ptr_dest++ = *ptr_src++;
	}
	return (dest);
}
