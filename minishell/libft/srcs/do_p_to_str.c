/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_p_to_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 22:19:34 by sbeylot           #+#    #+#             */
/*   Updated: 2022/05/27 22:19:34 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	int_len_hex(unsigned long long n)
{
	int	int_len;

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

static void	ft_putptr_fd(unsigned long long n, int fd)
{
	if (n >= 16)
		ft_putptr_fd(n / 16, fd);
	ft_putchar_fd(HEX_BASE[n % 16], fd);
}

int	do_p_to_str(va_list ap)
{
	unsigned long long	n_ptr;
	int					count;

	n_ptr = (unsigned long long)va_arg(ap, void *);
	count = 0;
	if (n_ptr == 0)
		count += write(FD, "(nil)", 5);
	else
	{
		count = write(FD, "0x", 2);
		ft_putptr_fd(n_ptr, FD);
		count += int_len_hex(n_ptr);
	}
	return (count);
}
