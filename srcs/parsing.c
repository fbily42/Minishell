/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:22:45 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/04 10:31:58 by sbeylot          ###   ########.fr       */
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

t_node	*parse_pipe(t_token **token)
{
	t_node	*node;

	node = parse_cmd(token);
	if (!node)
		return (NULL);
	while (*token && get_ttype(token) == PIPE)
	{
		node = node_pipe(&node, token);
		if (!node)
			return (clean_tree(&node), NULL);
	}
	return (node);
}

t_node	*parse_cmd(t_token **token)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = CMD;
	node->data.b.left = NULL;
	node->data.b.right = NULL;
	while (*token && get_ttype(token) != PIPE)
	{
		if (is_cmd_token(*token))
		{
			if (node->data.b.left != NULL)
				update_cmd(token, node->data.b.left);
			else
				node->data.b.left = node_arg(token);
			if (!node->data.b.left)
				return (clean_tree(&node), NULL);
		}
		else if (is_redirection_token(*token))
		{
			if (node->data.b.right != NULL)
				get_last_redir(node)->data.b.right = node_arg(token);
			else
				node->data.b.right = node_arg(token);
			if (!node->data.b.right)
				return (clean_tree(&node), NULL);
		}
	}
	return (node);
}
