/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:38:13 by fbily             #+#    #+#             */
/*   Updated: 2022/11/07 20:50:23 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Doit unset tout les PATH si plusieurs PATH
char	**unset(char **envp, char *var)
{
	char	**new_env;
	int		i;
	int		j;

	i = -1;
	j = 0 ;
	if (!*envp)
		return (envp);
	new_env = (char **)malloc(sizeof(char *) * (tab_len(envp) + 1));
	if (!new_env)
		return (free_2d(envp), NULL);
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], var, ft_strlen(var)) == NULL)
		{
			new_env[j] = ft_strdup(envp[i]);
			if (new_env[j] == NULL)
				return (free_2d(envp), NULL);
			j++;
		}
	}
	new_env[j] = NULL;
	free_2d(envp);
	return (new_env);
}

// if export A=xx B=yy >> Export les deux
char	**export(char **envp, char *var)
{
	char	**new_env;
	char	*to_find;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (check_var_name(var) == false)
		return (envp);
	to_find = find_var(var);
	if (!to_find)
		return (envp);
	if (!*envp)
	{
		new_env = (char **)malloc(sizeof(char *) * 2);
		new_env[0] = ft_strdup(var);
		if (new_env[j - 1] == NULL)
			return (free_2d(envp), NULL);
		new_env[1] = NULL;
	}
	else if (is_in_env(envp, var) == false)
	{
		new_env = (char **)malloc(sizeof(char *) * (tab_len(envp) + 2));
		if (!new_env)
			return (free_2d(envp), NULL);
		while (envp[++i])
		{
			new_env[i] = ft_strdup(envp[i]);
			if (new_env[j - 1] == NULL)
				return (free_2d(envp), NULL);
		}
		new_env[i] = ft_strdup(var);
		if (new_env[j - 1] == NULL)
			return (free_2d(envp), NULL);
		new_env[i] = NULL;
	}
	else
	{
		while (envp[++i])
		{
			if (ft_strnstr(envp[i], to_find, ft_strlen(to_find)) != NULL)
			{
				free(envp[i]);
				envp[i] = ft_strdup(var);
				if (!envp[i])
					return (free_2d(envp), NULL);
				return (envp);
			}
			i++;
		}
	}
	return (new_env);
}
