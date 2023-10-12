/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:17:34 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/06 18:58:50 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	**split_path(char *path)
{
	char	**ms_env;
	char	*copy;
	int		env_len;
	int		i;

	i = -1;
	ms_env = ft_split(path, ":");
	if (!ms_env)
		return (NULL);
	env_len = tab_len(ms_env);
	while (ms_env[++i])
	{
		copy = ft_strjoin(ms_env[i], "/");
		if (!copy)
			return (clean_tab(ms_env, env_len), NULL);
		free(ms_env[i]);
		ms_env[i] = ft_strdup(copy);
		free(copy);
		if (!ms_env[i])
			return (clean_tab(ms_env, env_len), NULL);
	}
	return (ms_env);
}

char	*get_path_env(char **envp, char *var)
{
	int		i;
	char	*path;

	i = -1;
	if (!envp)
		return (NULL);
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) == 0)
		{
			path = ft_substr(envp[i], ft_strlen(var), ft_strlen(envp[i]));
			if (!path)
				return (NULL);
			return (path);
		}
	}
	return (NULL);
}

char	**get_path(char **envp)
{
	char	*path;
	char	**ms_env;

	path = get_path_env(envp, "PATH=");
	if (!path)
		return (NULL);
	ms_env = split_path(path);
	if (!ms_env)
	{
		free(path);
		return (NULL);
	}
	free(path);
	return (ms_env);
}

char	**copy_env(char **envp)
{
	char	**ms_env;
	int		i;

	i = 0;
	ms_env = (char **)malloc(sizeof(char *) * (tab_len(envp) + 1));
	if (!ms_env)
		return (NULL);
	while (envp[i])
	{
		ms_env[i] = ft_strdup(envp[i]);
		i++;
	}
	ms_env[i] = NULL;
	return (ms_env);
}
