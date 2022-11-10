/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:09:28 by fbily             #+#    #+#             */
/*   Updated: 2022/11/09 21:55:43 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_var_name(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

bool	is_in_env(char	**envp, char *var)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], var, ft_strlen(var)) != NULL)
			return (true);
		i++;
	}
	return (false);
}

char	*find_var(char *var)
{
	char	*to_find;
	int		size;

	size = find_len_var(var);
	to_find = ft_substr(var, 0, size);
	if (!to_find)
		return (NULL);
	return (to_find);
}

int	find_len_var(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

unsigned int	ft_atoui(const char *nptr)
{
	int				i;
	int				j;
	unsigned int	nb;
	unsigned char	*cp_nptr;

	if (nptr == NULL)
		return (0);
	i = 0;
	j = 1;
	nb = 0;
	cp_nptr = (unsigned char *)nptr;
	while (cp_nptr[i] == 32 || (cp_nptr[i] >= 9 && cp_nptr[i] <= 13))
		i++;
	if (cp_nptr[i] == '-' || cp_nptr[i] == '+')
	{
		if (cp_nptr[i] == '-')
			j = -j;
		i++;
	}
	while (cp_nptr[i] >= '0' && cp_nptr[i] <= '9')
	{
		nb = nb * 10 + cp_nptr[i] - '0';
		i++;
	}
	return (nb * j);
}
