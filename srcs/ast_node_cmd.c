/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:24:06 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/10 13:18:11 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*node_arg(t_token **token, t_context *ctx)
{
	t_node	*node;

	node = NULL;
	if (*token && is_redirection_token(*token))
		node = node_redirection(token, ctx);
	else if (*token && is_cmd_token(*token))
	{
		node = (t_node *)malloc(sizeof(t_node));
		if (!node)
			return (NULL);
		node->data.c.cmd_len = cmd_length(*token);
		node->data.c.value = init_cmd(token, ctx);
		node->type = ARG;
		if (!node->data.c.value)
			return (clean_tree(&node), NULL);
	}
	return (node);
}

t_node	*node_pipe(t_node **tree, t_token **token, t_context *ctx)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (clean_tree(tree), NULL);
	eat_token(token);
	node->type = PIPE;
	if ((*tree)->type == CMD)
	{
		node->data.b.left = *tree;
		node->data.b.right = parse_cmd(token, ctx);
		if (!node->data.b.right)
			return (clean_tree(&node), NULL);
		*tree = node;
		return (node);
	}
	else
	{
		node->data.b.left = get_last_pipe(*tree)->data.b.right;
		node->data.b.right = parse_cmd(token, ctx);
		if (!node->data.b.right)
			return (clean_tree(tree), free(node), NULL);
		get_last_pipe(*tree)->data.b.right = node;
		return (*tree);
	}
}

t_node	*node_redirection(t_token **token, t_context *ctx)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = REDIR;
	node->data.b.left = init_redir(token, ctx);
	if (*token && is_redirection_token(*token))
	{
		node->data.b.right = node_arg(token, ctx);
		if (!node->data.b.right)
			return (clean_tree(&node), NULL);
	}
	else
		node->data.b.right = NULL;
	return (node);
}

char	**init_cmd(t_token **token, t_context *ctx)
{
	char	**tab;
	int		i;

	i = 0;
	tab = (char **)malloc(sizeof(char *) * (cmd_length(*token) + 1));
	if (!tab)
		return (NULL);
	while (*token && is_cmd_token(*token))
	{
		tab[i++] = extract_word(token, 1, ctx);
		if (!tab[i - 1])
			return (clean_tab(tab, i - 1), NULL);
	}
	tab[i] = NULL;
	return (tab);
}

int	cmd_length(t_token *token)
{
	t_token	*curr;
	size_t	len;

	curr = token;
	len = 0;
	while (curr && is_cmd_token(curr))
	{
		len++;
		next_token(&curr);
	}
	return (len);
}
