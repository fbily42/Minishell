/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 21:15:11 by fbily             #+#    #+#             */
/*   Updated: 2022/11/11 17:12:54 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_context *ctx, char **args)
{
	unsigned int	exit_code;

	ctx->error = ft_strdup("PopCornShell: exit: ");
	if (!args[1])
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit_and_clean(ctx, 0);
	}
	if (args[2])
	{
		ctx->error = strjoin_and_free_s1(ctx->error, "too many arguments\n");
		if (!ctx->error)
			error_malloc(ctx);
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd(ctx->error, STDERR_FILENO);
		free(ctx->error);
		ctx->error = NULL;
		return ;
	}
	check_arg_exit(ctx, args[1]);
	exit_code = ft_atoui(args[1]);
	ft_putstr_fd("exit\n", STDERR_FILENO);
	exit_and_clean(ctx, (unsigned char)exit_code);
}

void	check_arg_exit(t_context *ctx, char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
		{
			ctx->error = strjoin_and_free_s1(ctx->error, str);
			ctx->error = strjoin_and_free_s1(ctx->error,
					": numeric argument required\n");
			if (!ctx->error)
				error_malloc(ctx);
			ft_putstr_fd("exit\n", STDERR_FILENO);
			ft_putstr_fd(ctx->error, STDERR_FILENO);
			exit_and_clean(ctx, 2);
		}
		i++;
	}
}
