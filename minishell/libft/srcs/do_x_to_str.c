/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_x_to_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 22:19:13 by sbeylot           #+#    #+#             */
/*   Updated: 2022/05/27 22:19:13 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_int_len_h(unsigned int n)
{
	int				int_len;

	int_len = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		int_len++;
		n /= 16;
	}
	return (int_len);
}

static char	*ft_itoa_base(unsigned int n, int base, char type)
{
	char			*tab;
	unsigned int	nbr;
	int				index;

	nbr = n;
	index = ft_int_len_h(nbr);
	tab = (char *)malloc(sizeof(char) * ft_int_len_h(nbr) + 1);
	if (!tab)
		return (NULL);
	tab[index--] = '\0';
	if (nbr == 0)
		tab[index] = '0';
	while (nbr > 0)
	{
		if (type == 'x')
			tab[index--] = HEX_BASE[nbr % base];
		else
			tab[index--] = HEX_BASE_MAJ[nbr % base];
		nbr /= base;
	}
	return (tab);
}

int	do_x_to_str(va_list ap, char type)
{
	char				*str;
	int					count;
	unsigned int		nbr;

	nbr = va_arg(ap, unsigned int);
	str = ft_itoa_base(nbr, 16, type);
	if (str == NULL)
		return (-1);
	count = ft_strlen(str);
	ft_putstr_fd(str, FD);
	free(str);
	return (count);
}
