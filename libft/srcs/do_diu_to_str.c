/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_diu_to_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 22:19:04 by sbeylot           #+#    #+#             */
/*   Updated: 2022/05/27 22:19:04 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	do_di_to_str(va_list ap)
{
	char	*str;
	int		count;

	str = ft_itoa(va_arg(ap, int));
	if (str == NULL)
		return (-1);
	count = ft_strlen(str);
	ft_putstr_fd(str, FD);
	free(str);
	return (count);
}

static void	ft_putnbr_u_fd(unsigned int n, int fd)
{
	if (n > 9)
		ft_putnbr_u_fd(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}

int	do_u_to_str(va_list ap)
{
	unsigned int	nbr;
	int				count;

	nbr = va_arg(ap, unsigned int);
	count = 0;
	ft_putnbr_u_fd(nbr, FD);
	if (nbr == 0)
		count = 1;
	while (nbr)
	{
		count++;
		nbr /= 10;
	}
	return (count);
}
