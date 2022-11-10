/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:38:13 by fbily             #+#    #+#             */
/*   Updated: 2022/11/09 21:03:19 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**copy_unset(char **envp, char *var)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_env = (char **)malloc(sizeof(char *) * (tab_len(envp)));
	if (!new_env)
		return (NULL);
	while (envp[i])
	{
		if (ft_strnstr(envp[i], var, ft_strlen(var)) != NULL
			&& envp[i][ft_strlen(var)] == '=')
			i++;
		else
		{
			new_env[j] = ft_strdup(envp[i]);
			if (new_env[j] == NULL)
				return (NULL);
			j++;
			i++;
		}
	}
	new_env[j] = NULL;
	return (new_env);
}

char	**unset(char **envp, char *var)
{
	char	**new_env;

	new_env = NULL;
	if (!*envp || is_in_env(envp, var) == false || check_var_name(var) == true)
		return (envp);
	new_env = copy_unset(envp, var);
	if (!new_env)
		return (free_2d(envp), NULL);
	free_2d(envp);
	return (new_env);
}
