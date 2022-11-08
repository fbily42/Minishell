/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 20:24:25 by fbily             #+#    #+#             */
/*   Updated: 2022/11/06 20:44:18 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
TODO :
	CD chemin relatif ou absolu
	EXPORT no option
	UNSET no option
	ENV no option / no argument
	EXIT no option
*/

bool	is_built_in(t_node *tree, t_context *ctx)
{
	if (ft_strcmp(tree->data.c.value[0], "echo") == 0)
	{
		echo(tree->data.c.value, ctx->pipe[STDOUT_FILENO]);
		return (true);
	}
	else if (ft_strcmp(tree->data.c.value[0], "pwd") == 0)
	{
		pwd(ctx->pipe[STDOUT_FILENO]);
		return (true);
	}
	else if (ft_strcmp(tree->data.c.value[0], "env") == 0)
	{
		env(ctx->envp, ctx->pipe[STDOUT_FILENO]);
		return (true);
	}
	// else if (ft_strcmp(tree->data.c.value[0], "unset") == 0)
	// {
	// 	ctx->envp = unset(ctx->envp, tree->data.c.value[0]);
	// 	return (true);
	// }
	return (false);
}

void	echo(char **str, int fd)
{
	int	i;
	int	flag;

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

// fais segfault .. Need ***envp ?
char	**unset(char **envp, char *var)
{
	char	**new_env;
	int		i;
	int		j;

	i = -1;
	j = 0 ;
	if (!*envp)
		return (NULL);
	new_env = (char **)malloc(sizeof(char *) * (tab_len(envp) + 1));
	if (!new_env)
		return (free_2d(envp), NULL);
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], var, ft_strlen(var)) != 0)
		{
			new_env[j] = ft_strdup(envp[i]);
			if (new_env[j] == NULL)
			{
				free_until_k(new_env, j);
				return (free_2d(envp), NULL);
			}
			j++;
		}
	}
	new_env[j] = NULL;
	free_2d(envp);
	return (new_env);
}
