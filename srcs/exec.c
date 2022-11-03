/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:37:52 by fbily             #+#    #+#             */
/*   Updated: 2022/11/03 20:47:06 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// TODO : Recuperer tout les PIDs pour faire un waitpid dans l'ordre
//	afin de recuperer les exit_code. >>> Need compter toute les CMDs.
//	Gerer here_doc. Need modifier parsing pour gerer a mon niveau.
//	Makefile ne clean pas la libft ?? Maybe prendre ma libft + Makefile
//	Commencer a coder built-in + trouver conditions fork() > Uniquement si pipe

void	exec(t_node *tree, char **envp)
{
	t_context	ctx;
	int			childs;
	int			status;
	int			i;

	if (init_ctx(&ctx, envp) == false)
	{
		ft_putstr_fd("Problem with paths init\n", STDERR_FILENO);
		return ;
	}
	childs = exec_node(tree, &ctx);
	i = 0;
	if (childs == 0)
		return ;
	status = 0;
	while (i < childs)
	{
		waitpid(-1, &status, 0);
		i++;
	}
}

int	exec_node(t_node *tree, t_context *ctx)
{
	if (!tree)
		return (0);
	if (tree->type == CMD)
	{
		if (tree->data.b.right != NULL && tree->data.b.right->type == REDIR)
			if (update_redir(tree->data.b.right, ctx) == false)
				return (0);
		return (exec_cmd(tree->data.b.left, ctx));
	}
	else if (tree->type == PIPE)
		return (exec_pipe(tree, ctx));
	else
		return (0);
}

int	exec_pipe(t_node *tree, t_context *ctx)
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
	childs += exec_node(tree->data.b.left, &lhs_ctx);
	close(p[STDOUT_FILENO]);
	rhs_ctx = *ctx;
	rhs_ctx.pipe[STDIN_FILENO] = p[STDIN_FILENO];
	childs += exec_node(tree->data.b.right, &rhs_ctx);
	close(p[STDIN_FILENO]);
	return (childs);
}

int	exec_cmd(t_node *tree, t_context *ctx)
{
	if (fork() == 0)
	{
		dup2(ctx->pipe[STDIN_FILENO], STDIN_FILENO);
		if (ctx->pipe[STDIN_FILENO] > 2)
			close(ctx->pipe[STDIN_FILENO]);
		dup2(ctx->pipe[STDOUT_FILENO], STDOUT_FILENO);
		if (ctx->pipe[STDOUT_FILENO] > 2)
			close(ctx->pipe[STDOUT_FILENO]);
		if (ctx->fd_to_close >= 0)
			close(ctx->fd_to_close);
		execute_cmd(tree, ctx);
	}
	return (1);
}
