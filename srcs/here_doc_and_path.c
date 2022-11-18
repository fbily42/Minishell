/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_and_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:39:42 by fbily             #+#    #+#             */
/*   Updated: 2022/11/18 13:24:31 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_minishell_heredoc;

int	heredoc_error(char *heredoc, int fd[2], t_context *ctx, int tmp)
{
	if (g_minishell_heredoc == 1)
	{
		dup2(tmp, STDIN_FILENO);
		close(tmp);
		free(ctx->error);
		ctx->error = NULL;
		free(heredoc);
		g_minishell_heredoc = 0;
		return (-2);
	}
	if (heredoc == NULL)
		ft_putstr_fd(ctx->error, STDERR_FILENO);
	free(ctx->error);
	ctx->error = NULL;
	close(fd[1]);
	free(heredoc);
	g_minishell_heredoc = 0;
	return (fd[0]);
}

int	heredoc(t_node	*node, t_context *ctx)
{
	int		fd[2];
	int		tmp;
	char	*heredoc;

	if (pipe(fd) == -1)
		return (-1);
	ctx->error = ft_strjoin("Warning: here_doc wanted delimiter :",
			node->data.r.file);
	ctx->error = strjoin_and_free_s1(ctx->error, "\n");
	if (!ctx->error)
		error_malloc(ctx);
	g_minishell_heredoc = 2;
	tmp = dup(STDIN_FILENO);
	while (1)
	{
		heredoc = readline("> ");
		if (heredoc == NULL || ft_strcmp(heredoc, node->data.r.file) == 0)
			return (heredoc_error(heredoc, fd, ctx, tmp));
		heredoc = word_expansion(&heredoc, ctx);
		if (!heredoc)
			return (-1);
		ft_putendl_fd(heredoc, fd[1]);
		free(heredoc);
	}
	return (-1);
}

bool	find_paths(t_context *ctx)
{
	char	*path;
	int		i;

	i = 0;
	while (ctx->envp[i])
	{
		path = ft_strnstr(ctx->envp[i], "PATH=", 5);
		if (path)
		{	
			path = ft_substr(ctx->envp[i], 5, ft_strlen(ctx->envp[i]));
			if (!path)
				return (false);
			break ;
		}
		i++;
	}
	if (!path)
		return (true);
	ctx->my_paths = ft_split(path, ":");
	free(path);
	if (!*ctx->my_paths)
		return (false);
	if (create_paths(ctx) == false)
		return (false);
	return (true);
}

bool	create_paths(t_context *ctx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ctx->my_paths[j])
		j++;
	while (ctx->my_paths && ctx->my_paths[i])
	{
		ctx->my_paths[i] = strjoin_and_free_s1(ctx->my_paths[i], "/");
		if (ctx->my_paths[i] == NULL)
		{
			i = 0;
			while (i < j)
				free(ctx->my_paths[i++]);
			free(ctx->my_paths);
			ctx->my_paths = NULL;
			return (false);
		}
		i++;
	}
	return (true);
}

void	ft_close(t_context *ctx)
{
	if (ctx->pipe[STDIN_FILENO] > 2)
		close(ctx->pipe[STDIN_FILENO]);
	if (ctx->pipe[STDOUT_FILENO] > 2)
		close(ctx->pipe[STDOUT_FILENO]);
}
