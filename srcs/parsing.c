/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:22:45 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/20 18:55:57 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_minishell_exit[2];

t_node	*parsing(char *line, t_context *ctx)
{
	t_token	*token;
	t_node	*tree;

	tree = NULL;
	token = NULL;
	tokenizer(line, &token, ctx);
	if (!token)
		return (NULL);
	tree = parse_pipe(&token, ctx);
	if (!tree)
		return (free_token(&token), NULL);
	return (tree);
}

t_node	*parse_pipe(t_token **token, t_context *ctx)
{
	t_node	*node;

	node = parse_cmd(token, ctx);
	if (!node)
		return (NULL);
	while (*token && get_ttype(token) == PIPE)
	{
		node = node_pipe(&node, token, ctx);
		if (!node)
			return (clean_tree(&node), NULL);
	}
	return (node);
}

int	parse_do_cmd(t_token **token, t_node **node, t_context *ctx)
{
	if ((*node)->data.b.left != NULL)
		update_cmd(token, (*node)->data.b.left, ctx);
	else
		(*node)->data.b.left = node_arg(token, ctx);
	if (!(*node)->data.b.left)
		return (0);
	return (1);
}

int	parse_do_redir(t_token **token, t_node **node, t_context *ctx)
{
	t_node	*last;

	last = get_last_redir(*node);
	if ((*node)->data.b.right != NULL)
		last->data.b.right = node_arg(token, ctx);
	else
		(*node)->data.b.right = node_arg(token, ctx);
	if (!(*node)->data.b.right)
		return (0);
	return (1);
}

t_node	*parse_cmd(t_token **token, t_context *ctx)
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
			if (!parse_do_cmd(token, &node, ctx))
				return (clean_tree(&node), NULL);
		}
		else if (is_redirection_token(*token))
		{
			if (!parse_do_redir(token, &node, ctx))
				return (clean_tree(&node), NULL);
		}
	}
	return (node);
}
