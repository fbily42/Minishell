/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_cmd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:08:49 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/07 11:31:54 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * int	is_cmd_token(t_token *token)
 * @token:		Token List
 * ||	Check if the token is a cmd token
 *
 * int	is_redirection_token(t_token *token)
 * ||	Check if the token is a redirection one
 *
 * int	nbr_new_argument(t_token **token)
 * ||	Return the nbr of new elements for the cmd
 * ||	ex: echo Simon >Output Beylot Return 1
 * ||	the final cmd is echo Simon Beylot 
 *
 * int	update_cmd(t_token **token, t_node *tree)
 * @token:		Token List;
 * @tree:		Node needed to be update
 * ||	Update the cmd node if needed
 */

int	is_cmd_token(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == WORD || token->type == SQUOTE || token->type == DQUOTE)
		return (1);
	return (0);
}

int	is_redirection_token(t_token *token)
{
	if (token->type == REDIRIN)
		return (1);
	else if (token->type == REDIROUT)
		return (1);
	else if (token->type == APPEND)
		return (1);
	else if (token->type == HEREDOC)
		return (1);
	else if (token->type == IONUMBER)
		return (1);
	return (0);
}

int	nbr_new_argument(t_token **token)
{
	int		i;
	t_token	*cur;

	i = 0;
	cur = *token;
	while (cur && is_cmd_token(cur))
	{
		i++;
		cur = cur->next;
	}
	return (i);
}

int	update_cmd(t_token **token, t_node *tree)
{
	int		i;
	int		n_l;
	char	**n_cmd;

	i = -1;
	n_l = nbr_new_argument(token);
	n_cmd = (char **)malloc(sizeof(char *) * (tree->data.c.cmd_len + n_l + 1));
	if (!n_cmd)
		return (0);
	while (++i < tree->data.c.cmd_len)
	{
		n_cmd[i] = ft_strdup(tree->data.c.value[i]);
		if (!n_cmd[i])
			return (clean_tab(n_cmd, i - 1), 0);
	}
	while (*token && is_cmd_token(*token))
	{
		n_cmd[i++] = extract_word(token, 1);
		if (!n_cmd[i - 1])
			return (clean_tab(n_cmd, i - 1), 0);
	}
	n_cmd[i] = NULL;
	clean_tab(tree->data.c.value, tree->data.c.cmd_len);
	tree->data.c.value = n_cmd;
	return (1);
}
