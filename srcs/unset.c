/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:38:13 by fbily             #+#    #+#             */
/*   Updated: 2022/11/20 18:55:24 by sbeylot          ###   ########.fr       */
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

static bool	check_name_unset(char *var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		if (ft_isalnum(var[i]) == 1 || var[i] == '_')
			i++;
		else
			return (false);
	}
	return (true);
}

char	**unset(char **envp, char *var, t_context *ctx)
{
	char	**new_env;

	new_env = NULL;
	ctx->error = ft_strjoin("PopCornShell: unset: ", var);
	ctx->error = strjoin_and_free_s1(ctx->error, ": not a valid indetifier\n");
	if (!ctx->error)
		error_malloc(ctx);
	if (check_var_name(var) == true || check_name_unset(var) == false)
	{
		ft_putstr_fd(ctx->error, STDERR_FILENO);
		free(ctx->error);
		ctx->error = NULL;
		ctx->f_export += 1;
		return (envp);
	}
	if (!*envp || is_in_env(envp, var) == false)
		return (envp);
	new_env = copy_unset(envp, var);
	if (!new_env)
		return (free_2d(envp), NULL);
	free_2d(envp);
	free(ctx->error);
	ctx->error = NULL;
	return (new_env);
}

void	export_not_valid(t_context *ctx)
{
	ft_putstr_fd(ctx->error, STDERR_FILENO);
	free(ctx->error);
	ctx->error = NULL;
	ctx->f_export += 1;
}
