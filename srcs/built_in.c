/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 20:24:25 by fbily             #+#    #+#             */
/*   Updated: 2022/11/10 17:33:56 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
TODO :
	EXIT no option
*/

void	echo(char **str, int fd)
{
	int		i;
	bool	flag;

	(void)fd;
	i = 1;
	flag = 0;
	if (!*str || !str)
		return ;
	if (str[i])
	{
		if ((str[i][0] == '-' && str[i][1] == 'n'))
			flag = 1;
		while (str[i] && (str[i][0] == '-' && str[i][1] == 'n'))
			i++;
		while (str[i])
		{
			ft_putstr_fd(str[i], fd);
			if (str[i + 1])
				write(fd, " ", 1);
			i++;
		}
	}
	if (flag == 0)
		write(fd, "\n", 1);
}

void	pwd(int fd)
{
	char	dir[PATH_MAX];

	if (getcwd(dir, sizeof(dir)) == NULL)
		perror("Getcwd ");
	else
	{
		ft_putstr_fd(dir, fd);
		write(fd, "\n", 1);
	}
}

void	env(char **envp, int fd)
{
	int	i;

	i = 0;
	if (!*envp)
	{
		write(fd, "\n", 1);
		return ;
	}
	while (envp[i])
	{
		ft_putstr_fd(envp[i++], fd);
		write(fd, "\n", 1);
	}
}

void	cd(t_context *ctx, char	*path)
{
	char	dir[PATH_MAX];
	char	*oldpwd;
	char	*pwd;

	ctx->error = ft_strjoin("PopCornShell: ", "cd: ");
	ctx->error = strjoin_and_free_s1(ctx->error, path);
	if (getcwd(dir, sizeof(dir)) == NULL)
		perror("Getcwd ");
	oldpwd = ft_strjoin("OLDPWD=", dir);
	if (!oldpwd || !ctx->error)
	{
		ft_putstr_fd("Error malloc in cd\n", STDERR_FILENO);
		return ;
	}
	ctx->envp = export(ctx->envp, oldpwd);
	if (chdir(path) == -1)
		perror(ctx->error);
	free(oldpwd);
	if (getcwd(dir, sizeof(dir)) == NULL)
		perror("Getcwd ");
	pwd = ft_strjoin("PWD=", dir);
	if (!pwd)
	{
		ft_putstr_fd("Error malloc in cd\n", STDERR_FILENO);
		return ;
	}
	ctx->envp = export(ctx->envp, pwd);
	free(ctx->error);
	ctx->error = NULL;
}

//On doit free everthing si on exit ?
// Affiner message d'erreur
unsigned char	ft_exit(char *code)
{
	unsigned int	exit_code;

	if (!code)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		exit(0);
	}
	if (code[2] == '-' || code[2] == '+')
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("Numeric argument required\n", STDERR_FILENO);
		exit(2);
	}
	exit_code = ft_atoui(code);
	ft_putstr_fd("exit\n", STDERR_FILENO);
	exit((unsigned char)exit_code);
	return (0);
}
