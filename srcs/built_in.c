/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 20:24:25 by fbily             #+#    #+#             */
/*   Updated: 2022/11/16 16:05:04 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **str, int fd)
{
	int		flag;
	int		i;

	(void)fd;
	i = 1;
	flag = 0;
	i = check_option_echo(str, &flag);
	if (str[1])
	{
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

int	check_option_echo(char	**str, int *flag)
{
	int	i;
	int	j;

	i = 1;
	*flag = 0;
	while (str[i])
	{
		j = 0;
		if (str[i][j] == '-')
		{
			j++;
			while (str[i][j])
			{
				if (str[i][j] == 'n')
					j++;
				else
					return (i);
			}
			*flag = 1;
		}
		else
			return (i);
		i++;
	}
	return (i);
}

void	pwd(int fd)
{
	char	dir[PATH_MAX];

	if (getcwd(dir, sizeof(dir)) == NULL)
		perror("PopCornShell: pwd");
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
