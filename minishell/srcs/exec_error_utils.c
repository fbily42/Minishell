/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:06:40 by fbily             #+#    #+#             */
/*   Updated: 2022/11/16 17:10:24 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strjoin_and_free_s1(char *s1, char *s2)
{
	char	*back;

	back = ft_strjoin(s1, s2);
	if (!back)
		return (NULL);
	free(s1);
	return (back);
}

char	*strjoin_and_free_s2(char *s1, char *s2)
{
	char	*back;

	back = ft_strjoin(s1, s2);
	if (!back)
		return (NULL);
	free(s2);
	return (back);
}

void	print_error_cmd(t_context *ctx, t_node *tree)
{
	free(ctx->error);
	ctx->error = ft_strjoin("PopCornShell : ", tree->data.c.value[0]);
	ctx->error = strjoin_and_free_s1(ctx->error, " : Command not found\n");
	if (!ctx->error)
		error_malloc(ctx);
	ft_putstr_fd(ctx->error, STDERR_FILENO);
	free(ctx->error);
	ctx->error = NULL;
}

void	error_malloc(t_context *ctx)
{
	ft_putstr_fd("Error malloc\n", STDERR_FILENO);
	clean_struct(ctx);
	clean_tree(&ctx->root);
	if (ctx->pipe[STDIN_FILENO] > 2)
		close(ctx->pipe[STDIN_FILENO]);
	if (ctx->pipe[STDOUT_FILENO] > 2)
		close(ctx->pipe[STDOUT_FILENO]);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	close(STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	exit_and_clean(t_context *ctx, unsigned char code)
{
	clean_struct(ctx);
	clean_tree(&ctx->root);
	if (*ctx->envp)
		free_2d(ctx->envp);
	if (ctx->pipe[STDIN_FILENO] > 2)
		close(ctx->pipe[STDIN_FILENO]);
	if (ctx->pipe[STDOUT_FILENO] > 2)
		close(ctx->pipe[STDOUT_FILENO]);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	close(STDERR_FILENO);
	exit(code);
}
