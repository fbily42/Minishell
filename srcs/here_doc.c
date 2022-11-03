/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 20:39:42 by fbily             #+#    #+#             */
/*   Updated: 2022/11/03 20:42:37 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
Call get_here_doc to create here_doc
Return : TRUE if here_doc is create
Return : FALSE if something wrong happened.
*/
bool	open_here_doc(t_context *ctx, t_node *tree)
{
	if (get_here_doc(tree->data.r.file) == false)
		return (false);
	ctx->pipe[STDIN_FILENO] = open("tmp_hd", O_RDONLY);
	if (ctx->pipe[STDIN_FILENO] == -1)
	{
		perror("open : 'tmp_hd' ");
		return (false);
	}
	return (true);
}

/* 
Open a temporary file
Call create_here_doc
Return : TRUE if here_doc is create
Return : FALSE if something wrong happened.
*/
bool	get_here_doc(char *limiter)
{
	int		tmp_fd;

	tmp_fd = open("tmp_hd", O_CREAT | O_RDWR | O_APPEND, 0644);
	if (tmp_fd == -1)
	{
		perror("Tmp_here_doc ");
		return (false);
	}
	if (create_here_doc(limiter, tmp_fd) == false)
	{
		ft_putstr_fd("Error malloc here_doc\n", STDERR_FILENO);
		close(tmp_fd);
		return (false);
	}
	close(tmp_fd);
	return (true);
}

/* 
Use GNL to read in STDIN
Store readed line in temporary file
Return : TRUE at the end
Return : FALSE if something wrong happened.
*/
bool	create_here_doc(char *limiter, int tmp_fd)
{
	char	*line;
	char	*lim;
	char	*error;

	lim = ft_strjoin(limiter, "\n");
	error = ft_strjoin("\nWarning here_doc wanted delimiter : ", limiter);
	error = strjoin_and_free_s1(error, "\n");
	if (!lim || !error)
		return (free(lim), free(error), false);
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO, lim);
		if (ft_strncmp(line, lim, ft_strlen(lim)) == 0)
		{
			if (line == NULL)
				ft_putstr_fd(error, 2);
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		free(line);
	}
	return (free(lim), free(error), true);
}
