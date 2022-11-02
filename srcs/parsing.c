/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:22:45 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/02 10:09:24 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*parsing(char *line)
{
	t_token	*token;
	t_node	*tree;

	tree = NULL;
	token = NULL;
	tokenizer(line, &token);
	if (!token)
		return (NULL);
	//token_print(token);
	tree = parse_pipe(&token);
	if (!tree)
		return (free_token(&token), NULL);
	return (tree);
}

t_node	*parse_redir(t_token **token)
{
	t_node		*node;

	node = node_cmd(token, NULL);
	if (!node)
		return (NULL);
	while (*token && get_ttype(token) != PIPE)
	{
		if (is_cmd_token(*token))
		{
			if (!update_cmd(token, get_cmd_node(node)))
				return (clean_tree(&node), NULL);
		}
		else if (node->type == REDIR)
		{
			node = node_redirection(&node, token);
			if (!node)
				return (NULL);
		}
		else
		{
			node = node_redirection(&node, token);
		}
	}
	return (node);
}

t_node	*parse_pipe(t_token **token)
{
	t_node	*node;
	int		index;

	index = 1;
	node = parse_redir(token);
	if (!node)
		return (NULL);
	while (*token && get_ttype(token) == PIPE)
	{
		node = node_pipe(&node);
		if (!node)
			return (NULL);
		node->data.b.index = index++;
		eat_token(token);
		node->data.b.right = parse_redir(token);
		if (node->data.b.right == NULL)
			return (clean_tree(&node), NULL);
	}
	return (node);
}
