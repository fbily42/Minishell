/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 10:31:52 by sbeylot           #+#    #+#             */
/*   Updated: 2022/08/19 08:59:38 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_gnlclean_stash(t_gnl **stash)
{
	t_gnl	*new;
	t_gnl	*temp;
	int		i;
	int		j;

	new = malloc(sizeof(t_gnl));
	if (*stash == NULL || new == NULL)
		return ;
	new->next = NULL;
	temp = ft_gnllast(*stash);
	i = 0;
	while (temp->content[i] && temp->content[i] != '\n')
		i++;
	if (temp->content && temp->content[i] == '\n')
		i++;
	new->content = malloc(sizeof(char) * ft_strlen((temp->content + i)) + 1);
	if (new == NULL)
		return ;
	j = 0;
	while (temp->content[i])
		new->content[j++] = temp->content[i++];
	new->content[j] = '\0';
	ft_gnlclean(stash);
	*stash = new;
}

int	ft_is_newline(t_gnl *stash)
{
	int		i;
	t_gnl	*current;

	i = 0;
	if (stash == NULL)
		return (0);
	current = ft_gnllast(stash);
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_gnl_strlen(t_gnl *stash)
{
	int		i;
	int		str_len;
	t_gnl	*current;

	str_len = 0;
	if (stash == NULL)
		return (0);
	current = stash;
	while (current)
	{
		i = 0;
		while (current->content[i])
		{
			if (current->content[i] == '\n')
				return (str_len + 1);
			i++;
			str_len++;
		}
		current = current->next;
	}
	return (str_len);
}

void	ft_gnlclean(t_gnl **stash)
{
	t_gnl	*temp;

	if (*stash == NULL)
		return ;
	while (*stash)
	{
		temp = (*stash)->next;
		free((*stash)->content);
		free(*stash);
		*stash = temp;
	}
}
