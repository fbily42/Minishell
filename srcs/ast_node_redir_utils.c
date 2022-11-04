/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node_redir_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 07:43:20 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/04 12:56:24 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	init_node_redir(t_node **node)
{
	(*node)->data.r.fd = -1;
	(*node)->data.r.file = NULL;
}

void	assign_ionumber(t_node **node, t_token **token)
{
	t_token	*cur;

	if (!*token)
		return ;
	cur = (*token)->next;
	if (!cur)
		return ;
	(*node)->data.r.fd = ft_atoi(get_tstr(token));
	eat_token(token);
}

int	valid_redir(t_token *token)
{
	t_token	*cur;
	t_type	type;

	if (!token)
		return (0);
	cur = token;
	if (!cur->next)
		return (0);
	type = cur->type;
	if ((type == REDIRIN || type == REDIROUT || type == APPEND \
			|| type == HEREDOC) && cur->next->type == IOFILE)
		return (1);
	else
		return (0);
}

void	assign_redir(t_node **node, t_token **token)
{
	if (!*token)
		return ;
	if (get_ttype(token) == REDIRIN)
		(*node)->type = REDIRIN;
	else if (get_ttype(token) == HEREDOC)
		(*node)->type = HEREDOC;
	else if (get_ttype(token) == REDIROUT)
		(*node)->type = REDIROUT;
	else if (get_ttype(token) == APPEND)
		(*node)->type = APPEND;
	eat_token(token);
	if ((*node)->type == REDIRIN)
		(*node)->data.r.file = extract_word(token);
	else if ((*node)->type == REDIROUT)
		(*node)->data.r.file = extract_word(token);
	else if ((*node)->type == APPEND)
		(*node)->data.r.file = extract_word(token);
	else if ((*node)->type == HEREDOC)
		(*node)->data.r.file = extract_word(token);
}
