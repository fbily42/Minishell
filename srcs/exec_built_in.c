/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 21:16:10 by fbily             #+#    #+#             */
/*   Updated: 2022/11/13 22:40:12 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_built_in(t_node *tree)
{
	if (ft_strcmp(tree->data.c.value[0], "echo") == 0)
		return (true);
	else if (ft_strcmp(tree->data.c.value[0], "pwd") == 0)
		return (true);
	else if (ft_strcmp(tree->data.c.value[0], "env") == 0)
		return (true);
	else if (ft_strcmp(tree->data.c.value[0], "unset") == 0)
		return (true);
	else if (ft_strcmp(tree->data.c.value[0], "export") == 0)
		return (true);
	else if (ft_strcmp(tree->data.c.value[0], "cd") == 0)
		return (true);
	else if (ft_strcmp(tree->data.c.value[0], "exit") == 0)
		return (true);
	return (false);
}

bool	exec_built_in(t_node *tree, t_context *ctx, int fd)
{
	if (ft_strcmp(tree->data.c.value[0], "echo") == 0)
	{
		echo(tree->data.c.value, fd);
		return (true);
	}
	else if (ft_strcmp(tree->data.c.value[0], "pwd") == 0)
	{
		pwd(fd);
		return (true);
	}
	else if (ft_strcmp(tree->data.c.value[0], "env") == 0)
	{
		env(ctx->envp, fd);
		return (true);
	}
	else if (ft_strcmp(tree->data.c.value[0], "cd") == 0)
	{
		if (execute_cd(tree, ctx) == true)
			return (true);
		return (false);
	}
	else if (exec_unset_export_exit(tree, ctx) == true)
		return (true);
	return (false);
}

bool	execute_cd(t_node *tree, t_context *ctx)
{
	if (tree->data.c.value[1] != NULL)
	{
		if (tree->data.c.value[2] != NULL)
		{
			ctx->error = ft_strjoin("PopCornShell: ", "cd: ");
			ctx->error = strjoin_and_free_s1(ctx->error,
					"too many arguments\n");
			if (!ctx->error)
				error_malloc(ctx);
			ft_putstr_fd(ctx->error, STDERR_FILENO);
			free(ctx->error);
			ctx->error = NULL;
			return (false);
		}
		else
		{
			if (cd(ctx, tree->data.c.value[1]) == false)
				return (false);
		}
		return (true);
	}
	return (true);
}

bool	exec_unset_export_exit(t_node *tree, t_context *ctx)
{
	int	i;

	i = 1;
	if (ft_strcmp(tree->data.c.value[0], "unset") == 0)
	{
		if (tree->data.c.value[1] != NULL && *ctx->envp)
			while (tree->data.c.value[i])
				ctx->envp = unset(ctx->envp, tree->data.c.value[i++]);
		return (true);
	}
	else if (ft_strcmp(tree->data.c.value[0], "export") == 0)
	{
		if (tree->data.c.value[1] != NULL)
			while (tree->data.c.value[i])
				ctx->envp = export(ctx->envp, tree->data.c.value[i++]);
		else if (*ctx->envp)
			sort_and_print_env(ctx);
		return (true);
	}
	else if (ft_strcmp(tree->data.c.value[0], "exit") == 0)
		ft_exit(ctx, tree->data.c.value);
	return (false);
}
