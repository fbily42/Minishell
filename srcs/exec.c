/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:37:52 by fbily             #+#    #+#             */
/*   Updated: 2022/11/02 21:22:26 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(t_node *tree, char **envp)
{
	t_context	ctx;
	int			childs;
	int			i;

	ctx.pipe[0] = STDIN_FILENO;
	ctx.pipe[1] = STDOUT_FILENO;
	ctx.fd_to_close = -1;
	ctx.envp = envp;
	childs = exec_node(tree, &ctx);
	i = 0;
	while (i < childs)
	{
		wait(NULL);
		i++;
	}
}

int	exec_node(t_node *tree, t_context *ctx)
{
	if (!tree)
		return (0);
	if (tree->type == CMD)
		return (exec_cmd(tree->data.b.left, ctx));
	else if (tree->type == PIPE)
		return (exec_pipe(tree, ctx));
	else
		return (0);
}

int	exec_pipe(t_node *tree, t_context *ctx)
{
	t_node		*lhs;
	t_node		*rhs;
	t_context	lhs_ctx;
	t_context	rhs_ctx;
	int			p[2];
	int			childs;

	pipe(p);
	childs = 0;
	lhs = tree->data.b.left;
	lhs_ctx = *ctx;
	lhs_ctx.pipe[STDOUT_FILENO] = p[STDOUT_FILENO];
	lhs_ctx.fd_to_close = p[STDIN_FILENO];
	childs += exec_node(lhs, &lhs_ctx);
	rhs = tree->data.b.right;
	rhs_ctx = *ctx;
	rhs_ctx.pipe[STDIN_FILENO] = p[STDIN_FILENO];
	rhs_ctx.fd_to_close = p[STDOUT_FILENO];
	childs += exec_node(rhs, &rhs_ctx);
	close(p[STDIN_FILENO]);
	close(p[STDOUT_FILENO]);
	return (childs);
}

int	exec_cmd(t_node *tree, t_context *ctx)
{
	t_pipex	pipex;

	init_pipex(&pipex, ctx);
	if (fork() == 0)
	{
		dup2(ctx->pipe[STDIN_FILENO], STDIN_FILENO);
		dup2(ctx->pipe[STDOUT_FILENO], STDOUT_FILENO);
		if (ctx->fd_to_close >= 0)
			close(ctx->fd_to_close);
		execute_cmd(&pipex, tree);
	}
	return (1);
}
