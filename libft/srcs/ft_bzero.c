/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 11:47:46 by sbeylot           #+#    #+#             */
/*   Updated: 2022/05/03 12:18:40 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Input --
 * @s	:	Source
 * @n	:	Bytes to fill with 0
 * Return --
 * None
 */

#include "../includes/libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*ptr;

	if (s == NULL)
		return ;
	ptr = s;
	while (n--)
		*ptr++ = '\0';
}
