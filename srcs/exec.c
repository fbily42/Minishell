/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 09:52:35 by sbeylot           #+#    #+#             */
/*   Updated: 2022/10/28 22:06:16 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	init_pipe(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		pipex->pipe[i][0] = -1;
		pipex->pipe[i][1] = -1;
		i++;
	}
}

void	init_vars(t_pipex *pipex, char **envp, t_node *tree)
{
	pipex->envp = envp;
	pipex->error = NULL;
	pipex->cmd = NULL;
	pipex->fd_in = -1;
	pipex->fd_out = -1;
	pipex->status = 0;
	pipex->exit_code = 0;
	pipex->child_count = 0;
	pipex->pipe_index = 0;
	init_pipe(pipex);
	if (tree != NULL)
	{
		if (tree->type == PIPE)
		{
			pipex->pids = malloc(sizeof(int) * tree->data.b.index + 2);
			pipex->nb_cmd = tree->data.b.index + 2;
		}
		else
		{
			pipex->pids = malloc(sizeof(int));
			pipex->nb_cmd = 1;
		}
		if (pipex->pids == NULL)
			perror("Malloc pid");
	}
	if (find_paths(pipex) == false)
		return ;
}
// Gerer erreurs retour find_paths + Malloc pid.

void	clean_struct(t_pipex *pipex)
{
	if (pipex->error != NULL)
		free(pipex->error);
	if (pipex->cmd != NULL)
		free(pipex->cmd);
	if (pipex->my_paths != NULL)
		free_2d(pipex->my_paths);
	if (pipex->pids != NULL)
		free(pipex->pids);
}

void	execute_cmd(t_pipex *pipex, t_node *tree)
{
	if (pipex->fd_in != -1)
		redirect_in(pipex->fd_in);
	else if (pipex->nb_cmd != 1 && pipex->pipe[pipex->pipe_index % 3][0] != -1)
		redirect_in(pipex->pipe[pipex->pipe_index % 3][0]);
	if (pipex->fd_out != -1)
		redirect_out(pipex->fd_out);
	else if (pipex->nb_cmd != 1
		&& pipex->pipe[pipex->pipe_index % 3 + 1][1] != -1)
		redirect_out(pipex->fd_out);
	ft_close(pipex);
	if (find_cmd(pipex, tree) == true)
		execve(pipex->cmd, tree->data.c.value, pipex->envp);
	else
		exit(127);
}
//Gerer Erreurs redir'

bool	redirect_in(int new_in)
{
	if (dup2(new_in, STDIN_FILENO) == -1)
	{
		perror("Dup ");
		return (false);
	}
	return (true);
}

bool	redirect_out( int new_out)
{
	if (dup2(new_out, STDOUT_FILENO) == -1)
	{
		perror("Dup ");
		return (false);
	}
	return (true);
}

void	open_files(t_pipex *pipex, t_node *tree)
{
	if (tree->type == REDIRIN)
		open_file_in(pipex, tree);
	else if (tree->type == REDIROUT)
		open_file_out(pipex, tree);
}
//Gerer erreurs files -> exit(FAILURE)

bool	open_file_in(t_pipex *pipex, t_node *tree)
{
	if (pipex->fd_in != -1)
		close(pipex->fd_in);
	pipex->fd_in = open(tree->data.r.file, O_RDONLY);
	if (pipex->fd_in == -1)
	{
		pipex->error = ft_strjoin("open : ", tree->data.r.file);
		if (pipex->error)
		{
			perror(pipex->error);
			free(pipex->error);
			pipex->error = NULL;
		}
		else
			perror("malloc ");
		return (false);
	}
	return (true);
}

bool	open_file_out(t_pipex *pipex, t_node *tree)
{
	if (pipex->fd_out != -1)
		close(pipex->fd_out);
	pipex->fd_out = open(tree->data.r.file, O_CREAT
			| O_WRONLY | O_TRUNC, 0644);
	if (pipex->fd_out == -1)
	{
		pipex->error = ft_strjoin("open : ", tree->data.r.file);
		if (pipex->error)
		{
			perror(pipex->error);
			free(pipex->error);
			pipex->error = NULL;
		}
		else
			perror("malloc ");
		return (false);
	}
	return (true);
}

void	free_2d(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
		free(str[i++]);
	free(str);
	str = NULL;
}

/* 
Find the line "PATH=" in (char **)envp
Split every paths between " : "
Call create_paths
Return : TRUE if everything is OK
Return : FALSE if something wrong happened.
*/
bool	find_paths(t_pipex *pipex)
{
	char	*path;
	int		i;

	i = 0;
	while (pipex->envp[i])
	{
		path = ft_strnstr(pipex->envp[i], "PATH=", 5);
		if (path)
		{	
			path = ft_substr(pipex->envp[i], 5, ft_strlen(pipex->envp[i]));
			if (!path)
				return (false);
			break ;
		}
		i++;
	}
	if (!path)
		return (true);
	pipex->my_paths = ft_split(path, ":");
	free(path);
	if (!*pipex->my_paths)
		return (false);
	if (create_paths(pipex) == false)
		return (false);
	return (true);
}

/* 
Create every paths and store them if (char **)vars.my_paths
Return : TRUE if everything is OK
Return : FALSE if something wrong happened.
*/
bool	create_paths(t_pipex *pipex)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (pipex->my_paths[j])
		j++;
	while (pipex->my_paths && pipex->my_paths[i])
	{
		pipex->my_paths[i] = strjoin_and_free_s1(pipex->my_paths[i], "/");
		if (pipex->my_paths[i] == NULL)
		{
			i = 0;
			while (i < j)
				free(pipex->my_paths[i++]);
			free(pipex->my_paths);
			pipex->my_paths = NULL;
			return (false);
		}
		i++;
	}
	return (true);
}

/* 
Split argv to have the command and his options
Store if in (char **)vars.options
Check if this command is valid
If not, call check_path_cmd
Return : TRUE if everything is OK
Return : FALSE if something wrong happened.
*/
bool	find_cmd(t_pipex *pipex, t_node *tree)
{
	if (tree->data.c.value[0][0] == '.' && tree->data.c.value[0][1] == '/')
		return (print_error_dir(pipex, tree->data.c.value[0]), false);
	if (access(tree->data.c.value[0], F_OK | X_OK) == 0)
	{
		pipex->cmd = ft_strdup(tree->data.c.value[0]);
		if (pipex->cmd == NULL)
			return (false);
		return (true);
	}
	if (*pipex->envp != NULL && pipex->my_paths != NULL)
	{
		if (check_path_cmd(pipex, tree) == true)
			return (true);
	}
	print_error_cmd(pipex, tree->data.c.value[0]);
	return (false);
}

/* 
Test the command with every paths.
Return : TRUE if command is OK
Return : FALSE if something wrong happened or command not found.
*/
bool	check_path_cmd(t_pipex *pipex, t_node *tree)
{
	int	i;

	i = 0;
	while (pipex->my_paths[i])
	{
		pipex->cmd = ft_strjoin(pipex->my_paths[i], tree->data.c.value[0]);
		if (pipex->cmd == NULL)
			return (false);
		if (access(pipex->cmd, F_OK | X_OK) == 0)
			return (true);
		else
			free (pipex->cmd);
		i++;
	}
	pipex->cmd = NULL;
	return (false);
}

/*
Print message "Pipex: ARGV: Commant not found\n"
*/
void	print_error_cmd(t_pipex *pipex, char *argv)
{
	pipex->error = ft_strjoin(argv, ": Command not found\n");
	pipex->error = strjoin_and_free_s2("Pipex: ", pipex->error);
	if (!pipex->error)
		ft_putstr_fd("Error malloc\n", STDERR_FILENO);
	ft_putstr_fd(pipex->error, STDERR_FILENO);
	free(pipex->error);
	pipex->error = NULL;
}

/*
Print message "Pipex: ARGV: No such file or directory\n"
*/
void	print_error_dir(t_pipex *pipex, char *argv)
{
	pipex->error = ft_strjoin(argv, ": No such file or directory\n");
	pipex->error = strjoin_and_free_s2("Pipex: ", pipex->error);
	if (!pipex->error)
		ft_putstr_fd("Error malloc\n", STDERR_FILENO);
	ft_putstr_fd(pipex->error, STDERR_FILENO);
	free(pipex->error);
	pipex->error = NULL;
}

/*
Call ft_strjoin and free *s1
Same return as ft_strjoin.
*/
char	*strjoin_and_free_s1(char *s1, char *s2)
{
	char	*back;

	back = ft_strjoin(s1, s2);
	if (!back)
		return (NULL);
	free(s1);
	return (back);
}

/*
Call ft_strjoin and free *s2
Same return as ft_strjoin.
*/
char	*strjoin_and_free_s2(char *s1, char *s2)
{
	char	*back;

	back = ft_strjoin(s1, s2);
	if (!back)
		return (NULL);
	free(s2);
	return (back);
}
