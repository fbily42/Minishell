/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:01:41 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/09 22:20:38 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_minishell_exit;

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_node		*tree;
	t_context	ctx;

	(void)argc;
	(void)argv;
	line = NULL;
	tree = NULL;
	if (isatty(STDIN_FILENO) == 0)
	{
		perror("PopCornShell ");
		return (1);
	}
	g_minishell_exit = 0;
	if (*envp)
		ctx.envp = copy_env(envp);
	init_signal();
	while (1)
	{
		line = readline("🍿PopCornShell>> ");
		if (line == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}
		else if (*line && line[0])
			add_history(line);
		tree = parsing(line);
		exec(tree, &ctx);
		clean_tree(&tree);
		free(line);
	}
	free_2d(ctx.envp);
	return (0);
}