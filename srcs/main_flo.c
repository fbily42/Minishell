/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_flo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:01:41 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/06 20:38:16 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_minishell_exit;

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**my_env;
	t_node	*tree;

	(void)argc;
	(void)argv;
	line = NULL;
	tree = NULL;
	if (isatty(STDIN_FILENO) == 0)
	{
		perror("PopCornShell ");
		return (1);
	}
	my_env = (char **)malloc(sizeof(char *));
	if (my_env == NULL)
		return (ft_putstr_fd("Probleme with malloc\n", STDERR_FILENO), -1);
	my_env[0] = NULL;
	g_minishell_exit = 0;
	if (*envp)
		my_env = copy_env(envp);
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
//		tree_print(tree);
		exec(tree, my_env);
//		printf("Exit code : %d\n", g_minishell_exit);
		clean_tree(&tree);
		free(line);
	}
	return (0);
}
