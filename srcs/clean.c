/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:10:19 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/18 15:39:10 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_tab(char **tab, int index)
{
	while (index >= 0)
	{
		free(tab[index]);
		index--;
	}
	free(tab);
}

void	clean_cmd_node(t_node **node)
{
	if (!*node)
		return ;
	if ((*node)->data.c.value)
		clean_tab((*node)->data.c.value, (*node)->data.c.cmd_len);
	free(*node);
}

void	clean_tree(t_node **tree)
{
	if (tree == NULL)
		return ;
	if (*tree == NULL)
		return ;
	if ((*tree)->type == ARG)
	{
		clean_cmd_node(tree);
		return ;
	}
	if ((*tree)->type == APPEND || (*tree)->type == REDIRIN || \
			(*tree)->type == REDIROUT || (*tree)->type == HEREDOC)
	{
		free((*tree)->data.r.file);
		if ((*tree)->type == HEREDOC)
			close((*tree)->data.r.fd);
		free(*tree);
		return ;
	}
	clean_tree(&(*tree)->data.b.left);
	clean_tree(&(*tree)->data.b.right);
	free(*tree);
}
