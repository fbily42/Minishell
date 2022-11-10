/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 21:16:10 by fbily             #+#    #+#             */
/*   Updated: 2022/11/09 22:03:38 by fbily            ###   ########.fr       */
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

bool	exec_built_in(t_node *tree, t_context *ctx, bool flag)
{
	int	fd;
	int	i;

	i = 1;
	if (flag == 0)
		fd = ctx->pipe[STDOUT_FILENO];
	else
		fd = STDOUT_FILENO;
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
		if (tree->data.c.value[1] != NULL)
			cd(ctx, tree->data.c.value[1]);
		return (true);
	}
	else if (ft_strcmp(tree->data.c.value[0], "unset") == 0)
	{
		if (tree->data.c.value[1] != NULL && *ctx->envp)
		{
			while (tree->data.c.value[i])
			{
				ctx->envp = unset(ctx->envp, tree->data.c.value[i++]);
				if (!ctx->envp)
					return (false);
			}
		}
		return (true);
	}
	else if (ft_strcmp(tree->data.c.value[0], "export") == 0)
	{
		if (tree->data.c.value[1] != NULL)
		{
			while (tree->data.c.value[i])
			{
				ctx->envp = export(ctx->envp, tree->data.c.value[i++]);
				if (!ctx->envp)
					return (false);
			}
		}
		return (true);
	}
	else if (ft_strcmp(tree->data.c.value[0], "exit") == 0)
	{
		if (tree->data.c.value[1] != NULL)
			ft_exit(tree->data.c.value[1]);
		return (true);
	}
	return (false);
}
