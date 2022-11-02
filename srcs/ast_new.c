/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 21:17:38 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/02 10:43:00 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_parse_cmd(t_token **token)
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
				node->data.b.left = new_node_arg(token);
		}
		else if (is_redirection_token(*token))
		{
			if (node->data.b.right != NULL)
				get_last_redir(node)->data.b.right = new_node_arg(token);
			else
				node->data.b.right = new_node_arg(token);
		}
	}
	return (node);
}

t_node	*new_node_redirection(t_token **token)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = REDIR;
	node->data.b.left = init_redir(token);
	if (*token && is_redirection_token(*token))
		node->data.b.right = new_node_arg(token);
	else
		node->data.b.right = NULL;
	return (node);
}

t_node	*new_node_arg(t_token **token)
{
	t_node	*node;

	if (*token && is_redirection_token(*token))
		node = new_node_redirection(token);
	else if (*token && is_cmd_token(*token))
	{
		node = (t_node *)malloc(sizeof(t_node));
		if (!node)
			return (NULL);
		node->data.c.cmd_len = cmd_length(*token);
		node->data.c.value = init_cmd(token);
		node->type = ARG;
		if (!node->data.c.value)
			return (NULL);
	}
	return (node);
}

t_node	*new_node_pipe(t_node **tree, t_token **token)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	eat_token(token);
	node->data.b.index = 0;
	node->type = PIPE;
	if ((*tree)->type == CMD)
	{
		node->data.b.left = *tree;
		node->data.b.right = new_parse_cmd(token);
		*tree = node;
		return (node);
	}
	else
	{
		node->data.b.left = get_last_pipe(*tree)->data.b.right;
		node->data.b.right = new_parse_cmd(token);
		get_last_pipe(*tree)->data.b.right = node;
		return (*tree);
	}
}

t_node	*new_parse_pipe(t_token **token)
{
	t_node	*node;

	node = new_parse_cmd(token);
	if (!node)
		return (NULL);
	while (*token && get_ttype(token) == PIPE)
	{
		node = new_node_pipe(&node, token);
		if (!node)
			return (NULL);
	}
	return (node);
}

t_node	*new_parsing(char *line)
{
	t_token	*token;
	t_node	*tree;

	tree = NULL;
	token = NULL;
	tokenizer(line, &token);
	if (!token)
		return (NULL);
	//token_print(token);
	tree = new_parse_pipe(&token);
	if (!tree)
		return (free_token(&token), NULL);
	return (tree);
}

