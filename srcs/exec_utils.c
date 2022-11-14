/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 09:52:35 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/14 20:15:05 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	init_exec(t_node *tree, t_context *ctx, t_info *info)
{
	info->i = -1;
	info->child_count = 0;
	ctx->root = tree;
	ctx->nb_cmd = ast_cmd_number(tree, 0);
	info->pids = malloc(sizeof(int) * ctx->nb_cmd);
	if (!info->pids)
		return (false);
	info->p_int = info->pids;
	if (init_ctx(ctx) == false)
		return (false);
	ctx->pchild = info->pids;
	return (true);
}

bool	init_ctx(t_context *ctx)
{
	ctx->error = NULL;
	ctx->cmd = NULL;
	ctx->my_paths = NULL;
	ctx->pipe[0] = STDIN_FILENO;
	ctx->pipe[1] = STDOUT_FILENO;
	ctx->fd_to_close = -1;
	if (*ctx->envp)
		if (find_paths(ctx) == false)
			return (false);
	return (true);
}

void	clean_struct(t_context *ctx)
{
	if (ctx->error != NULL)
		free(ctx->error);
	if (ctx->cmd != NULL)
		free(ctx->cmd);
	if (ctx->my_paths != NULL)
		free_2d(ctx->my_paths);
	if (ctx->pchild != NULL)
		free(ctx->pchild);
}

void	free_2d(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		free(str[i++]);
	free(str);
	str = NULL;
}

int	ast_cmd_number(t_node *tree, int x)
{
	if (!tree)
		return (0);
	if (tree->type == CMD)
		return (1);
	x += ast_cmd_number(tree->data.b.left, 0);
	x += ast_cmd_number(tree->data.b.right, 0);
	return (x);
}
