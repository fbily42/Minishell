/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:38:33 by sbeylot           #+#    #+#             */
/*   Updated: 2022/05/09 15:08:37 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Input --
 * @s		: source of the extraction
 * @start	: Start index
 * @len		: Lenght of the new string
 * Return --
 * ptr on new string || Null if malloc fail
 */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	ptrlen;

	if (start > ft_strlen(s))
	{
		ptr = ft_strdup("");
		return (ptr);
	}
	ptrlen = ft_strlen(s + start);
	if (ptrlen < len)
		len = ptrlen;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}
