/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 08:12:44 by sbeylot           #+#    #+#             */
/*   Updated: 2022/05/11 11:38:28 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Add a string to another
 * Input --
 * @dst	:	Destination
 * @src	:	Source
 * @size:	Size of the destination
 * Return --
 * return the size of the final destinatiom
 * For the function to work, the size must be greater than the destination
 * In the case size < dst lenght, it will return
 */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	srclen;
	size_t	destlen;
	size_t	i;

	srclen = ft_strlen(src);
	destlen = ft_strlen(dest);
	if (size <= destlen)
		return (size + srclen);
	i = 0;
	while (src[i] != '\0' && (i + destlen + 1) < size)
	{
		dest[destlen + i] = src[i];
		i++;
	}
	dest[destlen + i] = '\0';
	return (destlen + srclen);
}
