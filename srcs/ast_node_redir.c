/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:18:40 by sbeylot           #+#    #+#             */
/*   Updated: 2022/10/28 20:46:39 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * t_node	*node_redirection(t_node **tree, t_token **token)
 * @tree:	AST
 * @token:	Token list
 * ||	Create two node, One for the direction & one with info
 * ||	Assign Redir type to it
 */

t_node	*node_redirection(t_node **tree, t_token **token)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (clean_tree(tree), NULL);
	node->type = REDIR;
//	node->index = 0;
	node->data.b.left = init_redir(token);
	if (!node->data.b.left)
		return (free(node), clean_tree(tree), NULL);
	if (tree)
		node->data.b.right = get_cmd_node(*tree);
	else
		node->data.b.right = NULL;
	if (tree && *tree && get_cmd_node(*tree) == NULL)
		return (node);
	else if (tree && *tree && (*tree)->type != CMD)
	{
		get_last_redir(*tree)->data.b.right = node;
		return (*tree);
	}
	else if (tree && *tree && (*tree)->type == CMD)
		node->data.b.right = *tree;
	return (node);
}

t_node	*node_pipe(t_node **tree)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (clean_tree(tree), NULL);
	node->data.b.left = *tree;
	node->data.b.right = NULL;
	*tree = node;
	node->type = PIPE;
	return (node);
}

t_node	*init_redir(t_token **token)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	init_node_redir(&node);
	if (get_ttype(token) == IONUMBER)
		assign_ionumber(&node, token);
	if (valid_redir(*token))
		assign_redir(&node, token);
	else
		return (free(node), NULL);
	return (node);
}
