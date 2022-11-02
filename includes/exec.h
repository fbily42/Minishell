/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:35:31 by fbily             #+#    #+#             */
/*   Updated: 2022/11/02 21:10:04 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

typedef struct s_pipex
{
	char		**envp;
	char		**my_paths;
	char		*error;
	char		*cmd;
	int			*pids;
	int			pipe[3][2];
	int			pipe_index;
	int			nb_cmd;
	int			fd_in;
	int			fd_out;
	int			status;
	int			exit_code;
	int			child_count;
}				t_pipex;

typedef struct s_context
{
	int		pipe[2];
	int		fd_to_close;
	char	**envp;
}				t_context;

void	init_pipex(t_pipex *pipex, t_context *ctx);
void	clean_struct(t_pipex *pipex);
void	execute_cmd(t_pipex *pipex, t_node *tree);
bool	open_files(t_pipex *pipex, t_node *tree);
bool	open_file_in(t_pipex *pipex, t_node *tree);
bool	open_file_out(t_pipex *pipex, t_node *tree);
void	free_2d(char **str);
bool	find_paths(t_pipex *pipex);
bool	create_paths(t_pipex *pipex);
bool	find_cmd(t_pipex *pipex, t_node *tree);
bool	check_path_cmd(t_pipex *pipex, t_node *tree);
void	print_error_cmd(t_pipex *pipex, char *argv);
void	print_error_dir(t_pipex *pipex, char *argv);
char	*strjoin_and_free_s1(char *s1, char *s2);
char	*strjoin_and_free_s2(char *s1, char *s2);
bool	redirect_in(int new_in);
bool	redirect_out( int new_out);
void	ft_close(t_pipex *pipex);
bool	error_msg(t_pipex *pipex, char *argv);

int		exec_cmd(t_node *tree, t_context *ctx);
int		exec_pipe(t_node *tree, t_context *ctx);
int		exec_node(t_node *tree, t_context *ctx);
void	exec(t_node *tree, char **envp);

#endif
