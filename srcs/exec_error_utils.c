/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:06:40 by fbily             #+#    #+#             */
/*   Updated: 2022/11/03 17:08:44 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Print message "PopCornShell: ARGV: Commant not found\n"
*/
void	print_error_cmd(t_context *ctx, char *argv)
{
	ctx->error = ft_strjoin(argv, ": Command not found\n");
	ctx->error = strjoin_and_free_s2("PopCornShell: ", ctx->error);
	if (!ctx->error)
		ft_putstr_fd("Error malloc\n", STDERR_FILENO);
	ft_putstr_fd(ctx->error, STDERR_FILENO);
	free(ctx->error);
	ctx->error = NULL;
}

bool	error_msg(t_context *ctx, char *argv)
{
	ctx->error = ft_strjoin("PopCornShell : ", argv);
	if (!ctx->error)
	{
		ft_putstr_fd("Error malloc\n", STDERR_FILENO);
		return (false);
	}
	return (true);
}

/*
Call ft_strjoin and free *s1
Same return as ft_strjoin.
*/
char	*strjoin_and_free_s1(char *s1, char *s2)
{
	char	*back;

	back = ft_strjoin(s1, s2);
	if (!back)
		return (NULL);
	free(s1);
	return (back);
}

/*
Call ft_strjoin and free *s2
Same return as ft_strjoin.
*/
char	*strjoin_and_free_s2(char *s1, char *s2)
{
	char	*back;

	back = ft_strjoin(s1, s2);
	if (!back)
		return (NULL);
	free(s2);
	return (back);
}
