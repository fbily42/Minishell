/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_flo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:06:43 by fbily             #+#    #+#             */
/*   Updated: 2022/10/31 19:43:07 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_minishell_env;

void	visit(t_node *tree, int value, t_pipex *pipex)
{
	if (!tree)
		return ;
	if (tree->type == CMD)
	{
		if (value == 0)
		{
			pipex->child_count++;
			pipex->pids[pipex->child_count - 1] = fork();
		}
		if (pipex->pids[pipex->child_count - 1] == 0)
			execute_cmd(pipex, tree);
		// else if (pipex->child_count % 3 == 0 && pipex->child_count > 2)
		// {
		// 	close(pipex->pipe[pipex->child_count % 3][0]);
		// 	close(pipex->pipe[pipex->child_count % 3][1]);
		// 	pipe(pipex->pipe[pipex->child_count]);
		// }
		return ;
	}
	if (tree->type == REDIR && value == 0)
	{
		pipex->child_count++;
		pipex->pids[pipex->child_count - 1] = fork();
		value = 1;
	}
	if (tree->type == REDIRIN || tree->type == REDIROUT)
	{
		if (pipex->pids[pipex->child_count - 1] == 0)
			if (open_files(pipex, tree) == false)
				exit(EXIT_FAILURE);
		return ;
	}
	if (tree->type == PIPE)
		value = 0;
	visit(tree->data.b.left, value, pipex);
	visit(tree->data.b.right, value, pipex);
	pipex->pipe_index++;
}

void	ft_close(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		close(pipex->pipe[i][0]);
		close(pipex->pipe[i][1]);
		i++;
	}
	if (pipex->fd_in != -1)
		close(pipex->fd_in);
	if (pipex->fd_out != -1)
		close(pipex->fd_out);
}

void	wait_all(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->pids[i])
		waitpid(pipex->pids[i++], &pipex->status, 0);
	if (WIFEXITED(pipex->status))
		pipex->exit_code = WEXITSTATUS(pipex->status);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_node	*tree;
	t_pipex	pipex;

	(void)argc;
	(void)argv;
	line = NULL;
	tree = NULL;
	g_minishell_env = envp;
	init_signal();
	while (1)
	{
		line = readline("🍿PopCornShell >> ");
		if (line == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}
		else if (*line && line[0])
			add_history(line);
		tree = parsing(line);
		init_vars(&pipex, envp, tree);
	//	tree_print(tree);
		visit(tree, 0, &pipex);
		ft_close(&pipex);
		wait_all(&pipex);
		clean_struct(&pipex);
		clean_tree(&tree);
		free(line);
	}
	return (0);
}
