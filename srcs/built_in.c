/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 20:24:25 by fbily             #+#    #+#             */
/*   Updated: 2022/11/04 21:13:10 by fbily            ###   ########.fr       */
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
