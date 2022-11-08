/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:37:52 by fbily             #+#    #+#             */
/*   Updated: 2022/11/06 19:58:02 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO : 
//	Commencer a coder built-in + trouver conditions fork() > Uniquement si pipe
//	exit_code : 126 == if (cmd ok but x_ok == -1)
//				ne marche pas avec signaux.
// info.pids a free dans les childs ??
// Check valgrind --track-fds=yes pour command not found

extern int	g_minishell_exit;

void	exec(t_node *tree, char **envp)
{
	t_context	ctx;
	t_info		info;

	if (init_exec(tree, &ctx, &info, envp) == false)
		return ;
	info.child_count = exec_node(tree, &ctx, info.p_int);
	if (info.child_count != 0)
	{
		while (info.i < info.child_count)
			waitpid(info.pids[info.i++], &info.status, 0);
		if (WIFEXITED(info.status))
			g_minishell_exit = WEXITSTATUS(info.status);
		else if (WIFSIGNALED(info.status))
			g_minishell_exit = WTERMSIG(info.status);
	}
	clean_struct(&ctx);
	free(info.pids);
}

int	exec_node(t_node *tree, t_context *ctx, int *p_int)
{
	if (!tree)
		return (0);
	if (tree->type == CMD)
	{
		if (tree->data.b.right != NULL && tree->data.b.right->type == REDIR)
			if (update_redir(tree->data.b.right, ctx) == false)
				return (0);
		if (tree->data.b.left)
			return (exec_cmd(tree->data.b.left, ctx, p_int));
		else
			return (0);
	}
	else if (tree->type == PIPE)
		return (exec_pipe(tree, ctx, p_int));
	else
		return (0);
}

int	exec_pipe(t_node *tree, t_context *ctx, int *p_int)
{
	t_context	lhs_ctx;
	t_context	rhs_ctx;
	int			p[2];
	int			childs;

	pipe(p);
	childs = 0;
	lhs_ctx = *ctx;
	lhs_ctx.pipe[STDOUT_FILENO] = p[STDOUT_FILENO];
	lhs_ctx.fd_to_close = p[STDIN_FILENO];
	childs += exec_node(tree->data.b.left, &lhs_ctx, p_int);
	close(p[STDOUT_FILENO]);
	p_int++;
	rhs_ctx = *ctx;
	rhs_ctx.pipe[STDIN_FILENO] = p[STDIN_FILENO];
	childs += exec_node(tree->data.b.right, &rhs_ctx, p_int);
	close(p[STDIN_FILENO]);
	return (childs);
}

int	exec_cmd(t_node *tree, t_context *ctx, int *p_int)
{
	if (ctx->nb_cmd == 1 && is_built_in(tree, ctx) == true)
		return (0);
	*p_int = fork();
	if (*p_int == -1)
	{
		perror("fork ");
		return (0);
	}
	if (*p_int == 0)
		child(tree, ctx);
	if (ctx->pipe[STDIN_FILENO] > 2)
		close(ctx->pipe[STDIN_FILENO]);
	if (ctx->pipe[STDOUT_FILENO] > 2)
		close(ctx->pipe[STDOUT_FILENO]);
	return (1);
}

void	child(t_node *tree, t_context *ctx)
{
	signal(SIGQUIT, SIG_DFL);
	dup2(ctx->pipe[STDIN_FILENO], STDIN_FILENO);
	if (ctx->pipe[STDIN_FILENO] > 2)
		close(ctx->pipe[STDIN_FILENO]);
	dup2(ctx->pipe[STDOUT_FILENO], STDOUT_FILENO);
	if (ctx->pipe[STDOUT_FILENO] > 2)
		close(ctx->pipe[STDOUT_FILENO]);
	if (ctx->fd_to_close >= 0)
		close(ctx->fd_to_close);
	if (is_built_in(tree, ctx) == true)
	{
		clean_struct(ctx);
		exit(0);
	}
	else
		execute_cmd(tree, ctx);
}
