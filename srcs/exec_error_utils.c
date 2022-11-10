/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:06:40 by fbily             #+#    #+#             */
/*   Updated: 2022/11/10 20:36:36 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	error_malloc(t_context *ctx)
{
	ft_putstr_fd("Error malloc\n", STDERR_FILENO);
	clean_struct(ctx);
	clean_tree(&ctx->root);
	exit(EXIT_FAILURE);
}

void	exit_and_clean(t_context *ctx, int code)
{
	clean_struct(ctx);
	clean_tree(&ctx->root);
	exit(code);
}
