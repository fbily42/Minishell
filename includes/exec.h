/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:35:31 by fbily             #+#    #+#             */
/*   Updated: 2022/11/03 20:30:36 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

typedef struct s_context
{
	int		pipe[2];
	int		fd_to_close;
	char	**envp;
	char	**my_paths;
	char	*error;
	char	*cmd;
}				t_context;

/**************		EXEC.C		**************/
int		exec_cmd(t_node *tree, t_context *ctx);
int		exec_pipe(t_node *tree, t_context *ctx);
int		exec_node(t_node *tree, t_context *ctx);
void	exec(t_node *tree, char **envp);

/**************		EXEC_REDIR_UTILS.C		**************/
bool	update_redir(t_node *tree, t_context *ctx);
bool	open_file_in(t_context *ctx, t_node *tree);
bool	open_file_out(t_context *ctx, t_node *tree, int flag);

/**************		EXEC_CMD_UTILS.C		**************/
bool	find_paths(t_context *ctx);
bool	create_paths(t_context *ctx);
bool	find_cmd(t_node *tree, t_context *ctx);
bool	check_path_cmd(t_context *ctx, t_node *tree);
void	execute_cmd(t_node *tree, t_context *ctx);

/**************		EXEC_ERROR_UTILS.C		**************/
void	print_error_cmd(t_context *ctx, char *argv);
bool	error_msg(t_context *ctx, char *argv);
char	*strjoin_and_free_s1(char *s1, char *s2);
char	*strjoin_and_free_s2(char *s1, char *s2);

/**************		EXEC_UTILS.C		**************/
bool	init_ctx(t_context *ctx, char **envp);
void	free_2d(char **str);
void	clean_struct(t_context *ctx);

#endif
