/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 22:19:28 by sbeylot           #+#    #+#             */
/*   Updated: 2022/05/27 22:19:28 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	is_valid_type(char type)
{
	int	i;

	i = -1;
	while (FLAG[++i])
	{
		if (type == FLAG[i])
			return (1);
	}
	return (-1);
}

static int	check_arg(va_list ap, char type)
{
	int	count;

	count = 0;
	if (type == 'c')
		count = do_c_to_str(ap);
	else if (type == 's')
		count = do_s_to_str(ap);
	else if (type == 'p')
		count = do_p_to_str(ap);
	else if (type == 'd' || type == 'i')
		count = do_di_to_str(ap);
	else if (type == 'u')
		count = do_u_to_str(ap);
	else if (type == 'x' || type == 'X')
		count = do_x_to_str(ap, type);
	else if (type == '%')
	{
		ft_putchar_fd('%', FD);
		count = 1;
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (is_valid_type(str[i]))
				count += check_arg(ap, str[i++]);
			else
				return (-1);
		}
		else
		{
			ft_putchar_fd(str[i++], FD);
			count++;
		}
	}
	va_end(ap);
	return (count);
}
