/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:13:12 by sbeylot           #+#    #+#             */
/*   Updated: 2022/05/11 11:58:46 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <limits.h>

static int	ft_int_len(int n)
{
	unsigned int	nbr;
	int				int_len;

	int_len = 0;
	if (n < 0)
	{
		nbr = -n;
		int_len++;
	}
	else
		nbr = n;
	if (nbr == 0)
		return (1);
	while (nbr)
	{
		int_len++;
		nbr /= 10;
	}
	return (int_len);
}

static unsigned int	ft_convert(int n)
{
	unsigned int	nbr;

	if (n < 0)
		nbr = -n;
	else
		nbr = n;
	return (nbr);
}

char	*ft_itoa(int n)
{
	char	*tab;
	size_t	nbr;
	int		index;

	index = ft_int_len(n);
	tab = (char *)malloc(sizeof(char) * ft_int_len(n) + 1);
	if (!tab)
		return (NULL);
	nbr = ft_convert(n);
	tab[index--] = '\0';
	if (nbr == 0)
		tab[index] = '0';
	while (nbr > 0)
	{
		tab[index--] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (n < 0)
		tab[index] = '-';
	return (tab);
}
