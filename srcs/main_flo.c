/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_flo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:01:41 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/03 20:40:40 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_minishell_env;

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
		tree = new_parsing(line);
//		tree_print(tree);
		exec(tree, envp);
		clean_tree(&tree);
		free(line);
	}
	return (0);
}
