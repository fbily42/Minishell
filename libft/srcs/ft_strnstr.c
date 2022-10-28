/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:22:16 by sbeylot           #+#    #+#             */
/*   Updated: 2022/05/06 17:51:20 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Input --
 * @big		:	string to look in
 * @little	:	string to look for
 * @len		:	Maximum lenght of the search in big
 * Return --
 * if @little empty == return (big)
 * if @little nowhere in big == NULL
 * else pointeur to the first character of little in big
 */

#include "../includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		k;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		j = 0;
		k = i;
		while (big[k] == little[j] && k < len)
		{
			k++;
			j++;
			if (little[j] == '\0')
				return ((char *)big + (k - j));
		}
		i++;
	}
	return (NULL);
}
