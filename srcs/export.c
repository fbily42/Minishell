/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:27:05 by fbily             #+#    #+#             */
/*   Updated: 2022/11/09 21:07:40 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_env(char *var)
{
	char	**new_env;

	new_env = (char **)malloc(sizeof(char *) * 2);
	new_env[0] = ft_strdup(var);
	if (!new_env || !new_env[0])
		return (NULL);
	new_env[1] = NULL;
	return (new_env);
}

static char	**add_new_var(char **envp, char *var)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (tab_len(envp) + 2));
	if (!new_env)
		return (NULL);
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		if (new_env[i] == NULL)
			return (NULL);
		i++;
	}
	new_env[i] = ft_strdup(var);
	if (new_env[i] == NULL)
		return (NULL);
	new_env[i + 1] = NULL;
	return (new_env);
}

static char	**update_var(char **envp, char *var, char *to_find)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], to_find, ft_strlen(to_find)) != NULL)
		{
			free(envp[i]);
			envp[i] = ft_strdup(var);
			if (!envp[i])
				return (free_2d(envp), free(to_find), NULL);
			free(to_find);
			return (envp);
		}
		i++;
	}
	return (envp);
}

char	**export(char **envp, char *var)
{
	char	**new_env;
	char	*to_find;

	new_env = NULL;
	to_find = find_var(var);
	if (!to_find)
		return (NULL);
	if (check_var_name(var) == false)
		return (envp);
	if (!*envp)
		new_env = create_env(var);
	else if (is_in_env(envp, to_find) == false)
		new_env = add_new_var(envp, var);
	else
	{
		envp = update_var(envp, var, to_find);
		return (envp);
	}
	free_2d(envp);
	return (new_env);
}
