/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:00:33 by fbily             #+#    #+#             */
/*   Updated: 2022/11/21 11:14:28 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	find_cmd(t_node *tree, t_context *ctx)
{
	if (tree->data.c.value[0][0] == '\0')
	{
		ft_putstr_fd("PopCornShell: '' : Command not found\n", STDERR_FILENO);
		return (false);
	}
	if (check_dot_slash(tree->data.c.value[0], ctx) == false)
		return (false);
	check_exceptions(tree->data.c.value[0], ctx);
	if (access(tree->data.c.value[0], F_OK) == 0)
	{
		ctx->cmd = ft_strdup(tree->data.c.value[0]);
		if (!ctx->cmd)
			error_malloc(ctx);
		free(ctx->error);
		return (true);
	}
	if (*ctx->envp != NULL && ctx->my_paths != NULL)
	{
		if (check_cmd_with_path(tree, ctx) == true)
			return (true);
	}
	print_error_cmd(ctx, tree);
	return (false);
}

bool	check_dot_slash(char *cmd, t_context *ctx)
{
	ctx->error = ft_strjoin("PopCornShell : ", cmd);
	if (!ctx->error)
		error_malloc(ctx);
	if ((cmd[0] == '.' && cmd[1] == '/') && access(cmd, F_OK) == -1)
	{
		perror(ctx->error);
		free(ctx->error);
		ctx->error = NULL;
		return (false);
	}
	ctx->error = strjoin_and_free_s1(ctx->error, " : Command not found\n");
	if (!ctx->error)
		error_malloc(ctx);
	if ((cmd[0] == '.' && (cmd[1] != '/' && cmd[1] != '\0')) || (cmd[0] == '/'
			&& access(cmd, F_OK) == -1))
	{
		ft_putstr_fd(ctx->error, STDERR_FILENO);
		free(ctx->error);
		ctx->error = NULL;
		return (false);
	}
	free(ctx->error);
	return (true);
}

bool	check_cmd_with_path(t_node *tree, t_context *ctx)
{
	int	i;

	i = 0;
	while (ctx->my_paths[i])
	{
		ctx->cmd = ft_strjoin(ctx->my_paths[i], tree->data.c.value[0]);
		if (ctx->cmd == NULL)
			error_malloc(ctx);
		if (access(ctx->cmd, F_OK) == 0)
			return (true);
		else
			free (ctx->cmd);
		i++;
	}
	ctx->cmd = NULL;
	return (false);
}

void	check_exceptions(char *cmd, t_context *ctx)
{
	ctx->error = ft_strjoin("PopCornShell : ", cmd);
	if (!ctx->error)
		error_malloc(ctx);
	if (cmd[0] == '.' && cmd[1] == '\0')
	{
		ctx->error = strjoin_and_free_s1(ctx->error,
				" : filename argument required\n");
		if (!ctx->error)
			error_malloc(ctx);
		ft_putstr_fd(ctx->error, STDERR_FILENO);
		exit_and_clean(ctx, 2);
	}
	ctx->error = strjoin_and_free_s1(ctx->error, ": Is a directory\n");
	if (!ctx->error)
		error_malloc(ctx);
	if ((cmd[0] == '.' || cmd[0] == '/')
		&& (cmd[1] == '.' || cmd[1] == '/' || cmd[1] == '\0'))
	{
		if (ft_strlen(cmd) > 1
			&& (cmd[2] != '/' && cmd[2] != '.' && cmd[2] != '\0'))
			return ;
		ft_putstr_fd(ctx->error, STDERR_FILENO);
		exit_and_clean(ctx, 126);
	}
}

void	execute_cmd(t_node *tree, t_context *ctx)
{
	if (find_cmd(tree, ctx) == true)
	{
		ctx->error = ft_strjoin("PopCornShell: ", tree->data.c.value[0]);
		if (!ctx->error)
			error_malloc(ctx);
		if (access(ctx->cmd, X_OK) == 0)
		{
			execve(ctx->cmd, tree->data.c.value, ctx->envp);
			if (ctx->cmd[0] != '/')
				perror("execve");
			else
			{
				ctx->error = strjoin_and_free_s1(ctx->error,
						": Is a directory\n");
				if (!ctx->error)
					error_malloc(ctx);
				ft_putstr_fd(ctx->error, STDERR_FILENO);
			}
		}
		else
			perror(ctx->error);
		exit_and_clean(ctx, 126);
	}
	else
		exit_and_clean(ctx, 127);
}
