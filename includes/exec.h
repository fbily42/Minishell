/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 20:16:06 by fbily             #+#    #+#             */
/*   Updated: 2022/10/27 23:26:24 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include <errno.h>
# include <stdbool.h>

typedef struct s_pipex
{
	char		**envp;
	char		**my_paths;
	char		*error;
	char		*cmd;
	int			*pids;
	int			fd_in;
	int			fd_out;
	int			status;
	int			exit_code;
	int			child_count;
}				t_pipex;

void	init_vars(t_pipex *pipex, char **envp, t_node *tree);
void	clean_struct(t_pipex *pipex);
void	execute_cmd(t_pipex *pipex, t_node *tree);
void	open_files(t_pipex *pipex, t_node *tree);
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

#endif