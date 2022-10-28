/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_flo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:06:43 by fbily             #+#    #+#             */
/*   Updated: 2022/10/28 22:05:14 by fbily            ###   ########.fr       */
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
			open_files(pipex, tree);
		return ;
	}
	if (tree->type == PIPE)
	{
		pipex->pipe_index = tree->data.b.index;
		pipe(pipex->pipe[tree->data.b.index % 3]);
		value = 0;
	}
	visit(tree->data.b.left, value, pipex);
	visit(tree->data.b.right, value, pipex);
}

void	ft_close(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (pipex->pipe[i][0] != -1)
			close(pipex->pipe[i][0]);
		if (pipex->pipe[i][1] != -1)
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
		line = readline("🍿PopCornshell >> ");
		if (line == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}
		else if (*line && line[0])
			add_history(line);
		tree = parsing(line);
		init_vars(&pipex, envp, tree);
		visit(tree, 0, &pipex);
		ft_close(&pipex);
		wait_all(&pipex);
		clean_struct(&pipex);
		clean_tree(&tree);
		free(line);
	}
	return (0);
}
