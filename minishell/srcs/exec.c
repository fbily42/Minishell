/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:37:52 by fbily             #+#    #+#             */
/*   Updated: 2022/11/20 18:14:22 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_minishell_exit[2];

void	exec(t_node *tree, t_context *ctx)
{
	t_info		info;

	if (tree == NULL)
		return ;
	g_minishell_exit[0] = 0;
	if (init_exec(tree, ctx, &info) == false)
		error_malloc(ctx);
	info.child_count = exec_node(tree, ctx, info.p_int);
	if (info.child_count != 0)
		wait_exit_code(ctx, info);
	clean_struct(ctx);
}

int	exec_node(t_node *tree, t_context *ctx, int *p_int)
{
	if (!tree)
		return (0);
	if (tree->type == CMD)
	{
		if (tree->data.b.right != NULL && tree->data.b.right->type == REDIR)
		{
			if (update_redir(tree->data.b.right, ctx) == false)
			{
				g_minishell_exit[0] = 1;
				*p_int = -1;
				ft_close(ctx);
				return (0);
			}
		}
		if (tree->data.b.left)
			return (exec_cmd(tree->data.b.left, ctx, p_int));
		else
		{
			*p_int = -2;
			return (0);
		}
	}
	else if (tree->type == PIPE)
		return (exec_pipe(tree, ctx, p_int));
	return (0);
}

int	exec_pipe(t_node *tree, t_context *ctx, int *p_int)
{
	t_context	lhs_ctx;
	t_context	rhs_ctx;
	int			p[2];
	int			childs;

	if (pipe(p) == -1)
	{
		perror("pipe");
		exit_and_clean(ctx, EXIT_FAILURE);
	}
	childs = 0;
	lhs_ctx = *ctx;
	lhs_ctx.pipe[STDOUT_FILENO] = p[STDOUT_FILENO];
	lhs_ctx.fd_to_close = p[STDIN_FILENO];
	childs += exec_node(tree->data.b.left, &lhs_ctx, p_int);
	p_int++;
	rhs_ctx = *ctx;
	rhs_ctx.pipe[STDIN_FILENO] = p[STDIN_FILENO];
	rhs_ctx.fd_to_close = p[STDOUT_FILENO];
	childs += exec_node(tree->data.b.right, &rhs_ctx, p_int);
	close(p[STDIN_FILENO]);
	close(p[STDOUT_FILENO]);
	return (childs);
}

int	exec_cmd(t_node *tree, t_context *ctx, int *p_int)
{
	if (ctx->nb_cmd == 1 && is_built_in(tree) == true)
	{
		if (exec_built_in(tree, ctx, ctx->pipe[STDOUT_FILENO]) == true)
			g_minishell_exit[0] = 0;
		else
			g_minishell_exit[0] = 1;
		ft_close(ctx);
		return (0);
	}
	*p_int = fork();
	if (*p_int == -1)
	{
		perror("fork ");
		return (0);
	}
	if (*p_int == 0)
		child(tree, ctx);
	ft_close(ctx);
	return (1);
}

void	child(t_node *tree, t_context *ctx)
{
	if (ctx->pipe[STDIN_FILENO] > 2)
	{
		dup2(ctx->pipe[STDIN_FILENO], STDIN_FILENO);
		close(ctx->pipe[STDIN_FILENO]);
	}
	if (ctx->pipe[STDOUT_FILENO] > 2)
	{
		dup2(ctx->pipe[STDOUT_FILENO], STDOUT_FILENO);
		close(ctx->pipe[STDOUT_FILENO]);
	}
	if (ctx->fd_to_close != -1)
		close(ctx->fd_to_close);
	if (is_built_in(tree) == true)
	{
		if (exec_built_in(tree, ctx, STDOUT_FILENO) == true)
			exit_and_clean(ctx, EXIT_SUCCESS);
		else
			exit_and_clean(ctx, EXIT_FAILURE);
	}
	else
		execute_cmd(tree, ctx);
}
