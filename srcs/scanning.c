/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:13:53 by sbeylot           #+#    #+#             */
/*   Updated: 2022/10/18 09:14:23 by sbeylot          ###   ########.fr       */
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
