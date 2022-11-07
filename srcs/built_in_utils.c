/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 20:09:28 by fbily             #+#    #+#             */
/*   Updated: 2022/11/07 20:50:25 by fbily            ###   ########.fr       */
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
