/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 16:26:21 by sbeylot           #+#    #+#             */
/*   Updated: 2022/05/11 11:54:53 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		size_s;

	size_s = ft_strlen(s1) + ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (size_s + 1));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, size_s + 1);
	ft_strlcat(ptr, s2, size_s + 1);
	return (ptr);
}
