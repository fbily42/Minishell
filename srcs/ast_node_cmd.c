/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:24:06 by sbeylot           #+#    #+#             */
/*   Updated: 2022/10/26 12:00:52 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 *	t_node	*node_cmd(t_token **token, t_node **tree)
 *	@token:		Token list
 *	@tree:		Abstract Synthax Tree
 *	||	Create a CMD node or create REDIR & REDIR_INFO Node for the tree 
 *
 *	char	**init_cmd(t_token **token)
 *	@token:		Token List
 *	||	Init the variable of the command node
 *
 * int		cmd_length(t_token *token)
 * @token:		Token list
 * ||	Return the length needed for the cmd array
 */

t_node	*node_cmd(t_token **token, t_node **tree)
{
	t_node	*node;

	node = NULL;
	if (*token && is_cmd_token(*token))
	{
		node = (t_node *)malloc(sizeof(t_node));
		if (!node)
			return (NULL);
		node->data.c.cmd_len = cmd_length(*token);
		node->data.c.value = init_cmd(token);
		node->type = CMD;
		if (!node->data.c.value)
			return (clean_tree(&node), NULL);
	}	
	else if (*token && is_redirection_token(*token))
	{
		node = node_redirection(tree, token);
		if (!node)
			return (clean_tree(&node), NULL);
		node->data.b.right = node_cmd(token, &node);
		if (!node->data.b.right)
			return (clean_tree(&node), NULL);
	}
	return (node);
}

char	**init_cmd(t_token **token)
{
	char	**tab;
	int		i;

	i = 0;
	tab = (char **)malloc(sizeof(char *) * (cmd_length(*token) + 1));
	if (!tab)
		return (NULL);
	while (*token && is_cmd_token(*token))
	{
		tab[i++] = extract_word(token);
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
