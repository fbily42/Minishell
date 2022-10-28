/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cs_to_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 22:18:54 by sbeylot           #+#    #+#             */
/*   Updated: 2022/05/31 11:04:17 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	do_c_to_str(va_list ap)
{
	unsigned char	c;

	c = va_arg(ap, int);
	ft_putchar_fd(c, FD);
	return (1);
}

int	do_s_to_str(va_list ap)
{
	int			count;
	const char	*sptr;
	int			i;

	i = -1;
	count = 0;
	sptr = va_arg(ap, const char *);
	if (sptr == NULL)
		count += write(FD, "(null)", 6);
	else
	{
		while (sptr[++i])
		{
			ft_putchar_fd(sptr[i], FD);
			count++;
		}
	}
	return (count);
}
