/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 23:27:13 by fbily             #+#    #+#             */
/*   Updated: 2022/11/18 23:28:54 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_minishell_exit[2];

void	wait_exit_code(t_context *ctx, t_info info)
{
	while (++info.i < ctx->nb_cmd)
	{
		if (info.pids[info.i] > 0)
			waitpid(info.pids[info.i], &info.status, 0);
	}
	if (g_minishell_exit[0] < 128)
	{
		if (WIFEXITED(info.status))
				g_minishell_exit[0] = WEXITSTATUS(info.status);
		else if (WIFSIGNALED(info.status))
				g_minishell_exit[0] = WTERMSIG(info.status) + 128;
	}
	if (info.pids[ctx->nb_cmd - 1] == -1)
		g_minishell_exit[0] = 1;
	else if (info.pids[ctx->nb_cmd - 1] == -2)
		g_minishell_exit[0] = 0;
}
