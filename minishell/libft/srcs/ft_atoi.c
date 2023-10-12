/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 14:21:24 by sbeylot           #+#    #+#             */
/*   Updated: 2022/08/17 17:27:40 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Convert a string to a int
 * Input --
 * @nptr	: String to convert
 * Return --
 * return an int
 */

#include "../includes/libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	neg_sign;
	int	result;

	i = 0;
	neg_sign = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg_sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * neg_sign);
}

static int	is_in_base(char c, int base)
{
	int	x;

	x = 0;
	while (x < base)
	{
		if (c == HEX_BASE_MAJ[x] || c == HEX_BASE[x])
			return (1);
		x++;
	}
	return (0);
}

static int	index_of(char c, int base)
{
	int	x;

	x = 0;
	while (x < base)
	{
		if (c == HEX_BASE_MAJ[x] || c == HEX_BASE[x])
			return (x);
		x++;
	}
	return (0);
}

int	ft_atoi_base(const char *nptr, int base)
{
	int	i;
	int	neg_sign;
	int	result;

	i = 0;
	neg_sign = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg_sign *= -1;
		i++;
	}
	while (is_in_base(nptr[i], base))
	{
		result = result * base + (index_of(nptr[i], base));
		i++;
	}
	return (result * neg_sign);
}
