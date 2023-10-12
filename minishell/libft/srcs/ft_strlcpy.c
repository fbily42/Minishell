/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 08:14:26 by sbeylot           #+#    #+#             */
/*   Updated: 2022/05/11 11:34:04 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Prototype -- size_t ft_strlcpy(char *dst, char *src, size_t size)
 * Input --
 * @dst : Destination of the function
 * @src : Source of the function
 * @size : Number of character copy
 * Return --
 * The total lenght of the string they tried to create (Length of src)
 */

#include "../includes/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	i;

	i = 0;
	if (!dst || !src)
		return (0);
	srclen = ft_strlen(src);
	if (size != 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srclen);
}
