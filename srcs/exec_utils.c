/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 09:52:35 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/03 17:19:37 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Initialise all varaibles in ctx to base value.
Return : FALSE if find_paths have somethig wrong
Return : TRUE if everything is ok.
*/
bool	init_ctx(t_context *ctx, char **envp)
{
	ctx->envp = envp;
	ctx->error = NULL;
	ctx->cmd = NULL;
	ctx->my_paths = NULL;
	ctx->pipe[0] = STDIN_FILENO;
	ctx->pipe[1] = STDOUT_FILENO;
	ctx->fd_to_close = -1;
	if (envp)
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
