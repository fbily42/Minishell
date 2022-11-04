/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 09:52:35 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/04 20:14:19 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	init_exec(t_node *tree, t_context *ctx, t_info *info, char **envp)
{
	info->i = 0;
	info->child_count = 0;
	ctx->nb_cmd = ast_cmd_number(tree, 0);
	info->pids = malloc(sizeof(int) * ctx->nb_cmd);
	if (!info->pids)
	{
		ft_putstr_fd("Problem with pids malloc\n", STDERR_FILENO);
		return (false);
	}
	info->p_int = info->pids;
	if (init_ctx(ctx, envp) == false)
	{
		ft_putstr_fd("Problem with paths init\n", STDERR_FILENO);
		free(info->pids);
		return (false);
	}
	return (true);
}

bool	init_ctx(t_context *ctx, char **envp)
{
	ctx->envp = envp;
	ctx->error = NULL;
	ctx->cmd = NULL;
	ctx->my_paths = NULL;
	ctx->pipe[0] = STDIN_FILENO;
	ctx->pipe[1] = STDOUT_FILENO;
	ctx->fd_to_close = -1;
	if (*envp)
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
