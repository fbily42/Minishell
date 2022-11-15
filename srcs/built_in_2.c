/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 21:15:11 by fbily             #+#    #+#             */
/*   Updated: 2022/11/15 21:06:02 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_context *ctx, char **args)
{
	long long	exit_code;

	ctx->error = ft_strdup("PopCornShell: exit: ");
	if (!args[1])
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit_and_clean(ctx, 0);
	}
	check_arg_exit(ctx, args[1], &exit_code);
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
	ft_putstr_fd("exit\n", STDERR_FILENO);
	exit_and_clean(ctx, (unsigned char)exit_code);
}

void	check_arg_exit(t_context *ctx, char *str, long long *exit_code)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	*exit_code = ft_atoll_capped(str, &flag);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0 || flag > 0)
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

static void	print_error_cd(t_context *ctx, char *oldpwd, char *path)
{
	if (ctx->error != NULL)
		free(ctx->error);
	ctx->error = ft_strjoin("PopCornShell: ", "cd: ");
	ctx->error = strjoin_and_free_s1(ctx->error, path);
	if (!ctx->error)
		error_malloc(ctx);
	perror(ctx->error);
	free(oldpwd);
	free(ctx->error);
	ctx->error = NULL;
}

bool	cd(t_context *ctx, char	*path)
{
	char	dir[PATH_MAX];
	char	*oldpwd;
	char	*pwd;

	oldpwd = NULL;
	if (getcwd(dir, sizeof(dir)) != NULL)
	{
		oldpwd = ft_strjoin("OLDPWD=", dir);
		if (!oldpwd)
			error_malloc(ctx);
	}
	if (chdir(path) == -1)
		return (print_error_cd(ctx, oldpwd, path), false);
	if (oldpwd)
	{
		ctx->envp = export(ctx->envp, oldpwd, ctx);
		free(oldpwd);
	}
	if (getcwd(dir, sizeof(dir)) != NULL)
	{
		pwd = ft_strjoin("PWD=", dir);
		if (!pwd)
			error_malloc(ctx);
		ctx->envp = export(ctx->envp, pwd, ctx);
		free(pwd);
	}
	return (true);
}
