/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:31:40 by sbeylot           #+#    #+#             */
/*   Updated: 2022/05/18 10:31:42 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_gnl	*ft_gnllast(t_gnl *lst)
{
	t_gnl	*temp;

	temp = lst;
	while (temp && temp->next != NULL)
		temp = temp->next;
	return (temp);
}

char	*get_next_line(int fd)
{
	static t_gnl	*stash;
	char			*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, line, 0) < 0)
		return (NULL);
	ft_read_write(fd, &stash);
	if (stash == NULL)
		return (NULL);
	ft_line_from_stash(stash, &line);
	ft_gnlclean_stash(&stash);
	if (line[0] == '\0')
	{
		ft_gnlclean(&stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

int	ft_read_write(int fd, t_gnl **stash)
{
	char	*buffer;
	int		c_read;

	c_read = 1;
	while (!(ft_is_newline(*stash)) && c_read != 0)
	{
		buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return (0);
		c_read = read(fd, buffer, BUFFER_SIZE);
		buffer[c_read] = '\0';
		ft_to_stash(stash, buffer, c_read);
		free(buffer);
	}
	return (c_read);
}

void	ft_to_stash(t_gnl **stash, char *buffer, int c_read)
{
	t_gnl	*new;
	t_gnl	*last;
	int		i;

	i = -1;
	if (c_read == 0)
		return ;
	new = malloc(sizeof(t_gnl));
	if (new == NULL)
		return ;
	new->next = NULL;
	new->content = (char *)malloc(sizeof(char) * (c_read + 1));
	if (new->content == NULL)
		return (free(new));
	while (buffer[++i])
		new->content[i] = buffer[i];
	new->content[i] = '\0';
	if ((*stash) == NULL)
		(*stash) = new;
	else
	{
		last = ft_gnllast(*stash);
		last->next = new;
	}
}

void	ft_line_from_stash(t_gnl *stash, char **line)
{
	int	i;
	int	y;
	int	str_len;

	y = 0;
	if (stash == NULL)
		return ;
	str_len = ft_gnl_strlen(stash);
	*line = (char *)malloc(sizeof(char) * (str_len + 1));
	if (*line == NULL)
		return ;
	while (str_len)
	{
		i = 0;
		while (stash->content[i] && str_len)
		{
			(*line)[y++] = stash->content[i++];
			str_len--;
		}
		stash = stash->next;
	}
	(*line)[y] = '\0';
}
