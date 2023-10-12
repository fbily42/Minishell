/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:27:05 by fbily             #+#    #+#             */
/*   Updated: 2022/11/21 10:49:55 by sbeylot          ###   ########.fr       */
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

static bool	check_name_export(t_context *ctx, char *var, int i)
{
	ctx->error = ft_strjoin("PopCornShell: export: ", var);
	ctx->error = strjoin_and_free_s1(ctx->error, ": not a valid indetifier\n");
	if (!ctx->error)
		error_malloc(ctx);
	if (ft_isdigit(var[0]) || var[0] == '=')
		return (export_not_valid(ctx), false);
	while (var[i])
	{
		if ((ft_isalnum(var[i]) == 1
				|| var[i] == '_' ))
			i++;
		else if (var[i] == '=' && i > 0)
			break ;
		else
		{
			ft_putstr_fd(ctx->error, STDERR_FILENO);
			free(ctx->error);
			ctx->error = NULL;
			ctx->f_export += 1;
			return (false);
		}
	}
	free(ctx->error);
	ctx->error = NULL;
	return (true);
}

char	**export(char **envp, char *var, t_context *ctx)
{
	char	**new_env;
	char	*to_find;

	new_env = NULL;
	if (check_name_export(ctx, var, 0) == false)
		return (envp);
	to_find = find_var(var);
	if (!to_find)
		error_malloc(ctx);
	if (!*envp)
		new_env = create_env(var);
	else if (is_in_env(envp, to_find) == false)
		new_env = add_new_var(envp, var);
	else
	{
		envp = update_var(envp, var, to_find);
		return (envp);
	}
	free(to_find);
	free_2d(envp);
	return (new_env);
}
