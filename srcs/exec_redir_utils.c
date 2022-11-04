/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:07:59 by fbily             #+#    #+#             */
/*   Updated: 2022/11/04 19:44:51 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	update_redir(t_node *tree, t_context *ctx)
{
	if (tree->data.b.left->type == REDIRIN
		|| tree->data.b.left->type == HEREDOC)
	{
		if (redir_in(tree, ctx) == false)
			return (false);
	}
	else if (tree->data.b.left->type == REDIROUT || APPEND)
	{
		if (redir_out(tree, ctx) == false)
			return (false);
	}
	if (tree->data.b.right != NULL)
		update_redir(tree->data.b.right, ctx);
	return (true);
}

bool	redir_in(t_node *tree, t_context *ctx)
{
	if (tree->data.b.left->type == REDIRIN)
	{
		if (ctx->pipe[STDIN_FILENO] > 2)
			close(ctx->pipe[STDIN_FILENO]);
		if (open_file_in(ctx, tree->data.b.left) == false)
			return (false);
	}
	else if (tree->data.b.left->type == HEREDOC)
	{
		if (ctx->pipe[STDIN_FILENO] > 2)
			close(ctx->pipe[STDIN_FILENO]);
		ctx->pipe[STDIN_FILENO] = heredoc(tree->data.b.left, ctx);
		if (ctx->pipe[STDIN_FILENO] == -1)
		{
			ft_putstr_fd("Problem occured with here_doc\n", STDERR_FILENO);
			return (false);
		}
	}
	return (true);
}

bool	redir_out(t_node *tree, t_context *ctx)
{
	if (tree->data.b.left->type == REDIROUT)
	{
		if (ctx->pipe[STDOUT_FILENO] > 2)
			close(ctx->pipe[STDOUT_FILENO]);
		if (open_file_out(ctx, tree->data.b.left, 0) == false)
			return (false);
	}
	else if (tree->data.b.left->type == APPEND)
	{
		if (ctx->pipe[STDOUT_FILENO] > 2)
			close(ctx->pipe[STDOUT_FILENO]);
		if (open_file_out(ctx, tree->data.b.left, 1) == false)
			return (false);
	}
	return (true);
}

bool	open_file_in(t_context *ctx, t_node *tree)
{
	if (ctx->pipe[0] > 2)
		close(ctx->pipe[0]);
	ctx->pipe[0] = open(tree->data.r.file, O_RDONLY);
	if (ctx->pipe[0] == -1)
	{
		ctx->error = ft_strjoin("open : ", tree->data.r.file);
		if (ctx->error)
		{
			perror(ctx->error);
			free(ctx->error);
			ctx->error = NULL;
		}
		else
			perror("malloc ");
		return (false);
	}
	return (true);
}

bool	open_file_out(t_context *ctx, t_node *tree, bool flag)
{
	if (ctx->pipe[1] > 2)
		close(ctx->pipe[1]);
	if (flag == 0)
		ctx->pipe[1] = open(tree->data.r.file, O_CREAT
				| O_WRONLY | O_TRUNC, 0644);
	else if (flag == 1)
		ctx->pipe[1] = open(tree->data.r.file, O_CREAT
				| O_WRONLY | O_APPEND, 0644);
	if (ctx->pipe[1] == -1)
	{
		ctx->error = ft_strjoin("open : ", tree->data.r.file);
		if (ctx->error)
		{
			perror(ctx->error);
			free(ctx->error);
			ctx->error = NULL;
		}
		else
			perror("malloc ");
		return (false);
	}
	return (true);
}
