/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_flo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:01:41 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/04 13:15:28 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_minishell_env;

int  ast_cmd_number(t_node *tree, int x)
{
	if (!tree)
		return (0);
	if (tree->type == CMD)
		return (1);
	x += ast_cmd_number(tree->data.b.left, 0);
	x += ast_cmd_number(tree->data.b.right, 0);
	return (x);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_node	*tree;

	(void)argc;
	(void)argv;
	g_minishell_env = envp;
	line = NULL;
	tree = NULL;
	init_signal();
	while (1)
	{
		line = readline("🍿PopCornshell >> ");
		if (line == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}
		else if (*line && line[0])
			add_history(line);
		tree = parsing(line);
		tree_print(tree);
		printf("Nombre de Cmd[%d]\n", ast_cmd_number(tree, 0));
		exec(tree, envp);
		clean_tree(&tree);
		free(line);
	}
	return (0);
}
