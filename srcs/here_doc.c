/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:39:42 by fbily             #+#    #+#             */
/*   Updated: 2022/11/04 19:34:14 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(t_node	*node, t_context *ctx)
{
	int		fd[2];
	char	*heredoc;

	if (pipe(fd) == -1)
		return (-1);
	ctx->error = ft_strjoin("Warning: here_doc wanted delimiter :",
			node->data.r.file);
	ctx->error = strjoin_and_free_s1(ctx->error, "\n");
	if (!ctx->error)
		return (-1);
	while (1)
	{
		heredoc = readline("> ");
		if (heredoc == NULL || ft_strcmp(heredoc, node->data.r.file) == 0)
		{
			if (heredoc == NULL)
				ft_putstr_fd(ctx->error, STDERR_FILENO);
			free(ctx->error);
			ctx->error = NULL;
			close(fd[1]);
			return (fd[0]);
		}
		ft_putendl_fd(heredoc, fd[1]);
		free(heredoc);
	}
}
