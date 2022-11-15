/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:09:28 by fbily             #+#    #+#             */
/*   Updated: 2022/11/15 20:44:57 by fbily            ###   ########.fr       */
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

long long	ft_atoll_capped(const char *nptr, int *flag)
{
	int				j;
	long long		nb;

	if (nptr == NULL)
		return (0);
	j = 1;
	nb = 0;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			j = -j;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (j > 0 && (LLONG_MAX - *nptr + '0') / 10 < nb)
			return (++*flag, 0);
		if (j < 0 && (LLONG_MAX + *nptr - '0') / 10 > -nb)
			return (++*flag, 0);
		nb = nb * 10 + *nptr - '0';
		nptr++;
	}
	return (nb * j);
}
