/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 20:24:25 by fbily             #+#    #+#             */
/*   Updated: 2022/11/07 20:52:27 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
TODO :
	CD chemin relatif ou absolu
	EXPORT no option
	EXIT no option
*/

bool	is_built_in(t_node *tree)
{
	if (ft_strcmp(tree->data.c.value[0], "echo") == 0)
		return (true);
	else if (ft_strcmp(tree->data.c.value[0], "pwd") == 0)
		return (true);
	else if (ft_strcmp(tree->data.c.value[0], "env") == 0)
		return (true);
	else if (ft_strcmp(tree->data.c.value[0], "unset") == 0)
		return (true);
	else if (ft_strcmp(tree->data.c.value[0], "export") == 0)
		return (true);
	return (false);
}

bool	exec_built_in(t_node *tree, t_context *ctx, bool flag)
{
	int	fd;

	if (flag == 0)
		fd = ctx->pipe[STDOUT_FILENO];
	else
		fd = STDOUT_FILENO;
	if (ft_strcmp(tree->data.c.value[0], "echo") == 0)
	{
		echo(tree->data.c.value, fd);
		return (true);
	}
	else if (ft_strcmp(tree->data.c.value[0], "pwd") == 0)
	{
		pwd(fd);
		return (true);
	}
	else if (ft_strcmp(tree->data.c.value[0], "env") == 0)
	{
		env(ctx->envp, fd);
		return (true);
	}
	else if (ft_strcmp(tree->data.c.value[0], "unset") == 0)
	{
		if (tree->data.c.value[1] != NULL && *ctx->envp)
			ctx->envp = unset(ctx->envp, tree->data.c.value[1]);
		return (true);
	}
	else if (ft_strcmp(tree->data.c.value[0], "unset") == 0)
	{
		if (tree->data.c.value[1] != NULL)
			ctx->envp = export(ctx->envp, tree->data.c.value[1]);
		return (true);
	}
	return (false);
}

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
