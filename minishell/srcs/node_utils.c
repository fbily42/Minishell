/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 08:05:13 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/06 19:22:14 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	get_ttype(t_token **token)
{
	return ((*token)->type);
}

char	*get_tstr(t_token **token)
{
	return ((*token)->location.start);
}

size_t	get_tlen(t_token **token)
{
	return ((*token)->location.len);
}

t_node	*get_last_redir(t_node *node)
{
	if (!node)
		return (NULL);
	if (node->data.b.right == NULL)
		return (node);
	if (node->data.b.right->type == CMD)
		return (node);
	return (get_last_redir(node->data.b.right));
}

t_node	*get_last_pipe(t_node *node)
{
	if (!node)
		return (NULL);
	if (node->data.b.right->type != PIPE)
		return (node);
	return (get_last_pipe(node->data.b.right));
}
