/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:34:29 by sbeylot           #+#    #+#             */
/*   Updated: 2022/05/11 11:52:22 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	sizecalloc;

	sizecalloc = nmemb * size;
	ptr = malloc(sizecalloc);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, sizecalloc);
	return (ptr);
}
