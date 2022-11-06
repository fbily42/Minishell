/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:11:36 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/06 18:20:44 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_node_cmd(t_node *node)
{
	int	i;

	i = -1;
	if (!node)
		return ;
	while (node->data.c.value[++i])
	{
		printf("\"%s\"", node->data.c.value[i]);
		if (node->data.c.value[i + 1] != 0)
			printf(",");
	}
}

void	print_node_redir(t_node *node)
{
	if (!node)
		return ;
	printf("--[Type:%s", debug_node_type(node->type));
	printf(" -- FD:%d -- File:%s", node->data.r.fd, node->data.r.file);
	printf("]\n");
}

void	printtab(int ntab)
{
	int	i;

	i = -1;
	while (++i < ntab)
		printf("\t\t");
}

void	print_tree_recur(t_node *tree, int level)
{
	if (tree == NULL)
	{
		printtab(level);
		printf("--[null]\n");
		return ;
	}
	if (tree->type == CMD || tree->type == APPEND || tree->type == HEREDOC || \
			tree->type == REDIRIN || tree->type == REDIROUT)
	{
		printtab(level);
		if (tree->type == CMD)
		{
			printf("--[");
			print_node_cmd(tree);
			printf("]\n");
		}
		else
			print_node_redir(tree);
		return ;
	}
	print_tree_recur(tree->data.b.right, level + 1);
	printtab(level);
	if (tree->type == PIPE)
		printf("[%d]", tree->data.b.index);
	printf("--[%s]\n", debug_node_type(tree->type));
	print_tree_recur(tree->data.b.left, level + 1);
}

void	new_print_tree_recur(t_node *tree, int level)
{
	if (tree == NULL)
	{
		printtab(level);
		printf("--[null]\n");
		return ;
	}
	if (tree->type == ARG || tree->type == APPEND || tree->type == HEREDOC || \
			tree->type == REDIRIN || tree->type == REDIROUT)
	{
		printtab(level);
		if (tree->type == ARG)
		{
			printf("--[");
			print_node_cmd(tree);
			printf("]\n");
		}
		else
			print_node_redir(tree);
		return ;
	}
	new_print_tree_recur(tree->data.b.right, level + 1);
	printtab(level);
	if (tree->type == PIPE)
		printf("[%d]", tree->data.b.index);
	printf("--[%s]\n", debug_node_type(tree->type));
	new_print_tree_recur(tree->data.b.left, level + 1);
}

void	tree_print(t_node *tree)
{
	printf("\n-------------------------------------------------------\n");
	new_print_tree_recur(tree, 0);
	printf("-------------------------------------------------------\n");
}
