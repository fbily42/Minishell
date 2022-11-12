/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:13:53 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/12 14:10:23 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	eat_token(t_token **token)
{
	t_token	*temp;

	if (*token == NULL)
		return ;
	temp = (*token)->next;
	free(*token);
	*token = temp;
}

void	next_token(t_token **token)
{
	if (!*token)
		return ;
	*token = (*token)->next;
}

int  readline_is_empty(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (!is_whitespace(line[i]))
			return (0);
	}
	return (1);
}
