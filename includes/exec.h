/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:35:31 by fbily             #+#    #+#             */
/*   Updated: 2022/11/10 10:50:52 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include <limits.h>

typedef struct s_info
{
	int			child_count;
	int			status;
	int			i;
	int			*pids;
	int			*p_int;
}				t_info;

/**************		EXEC.C		**************/
int				exec_pipe(t_node *tree, t_context *ctx, int *p_int);
int				exec_node(t_node *tree, t_context *ctx, int *p_int);
int				exec_cmd(t_node *tree, t_context *ctx, int *p_int);
void			child(t_node *tree, t_context *ctx);
void			exec(t_node *tree, t_context *ctx);

/**************		EXEC_REDIR_UTILS.C		**************/
bool			open_file_out(t_context *ctx, t_node *tree, bool flag);
bool			update_redir(t_node *tree, t_context *ctx);
bool			open_file_in(t_context *ctx, t_node *tree);
bool			redir_out(t_node *tree, t_context *ctx);
bool			redir_in(t_node *tree, t_context *ctx);

/**************		HERE_DOC.C		**************/
int				heredoc(t_node	*node, t_context *ctx);

/**************		EXEC_CMD_UTILS.C		**************/
bool			check_path_cmd(t_context *ctx, t_node *tree);
void			execute_cmd(t_node *tree, t_context *ctx);
bool			find_cmd(t_node *tree, t_context *ctx);
bool			create_paths(t_context *ctx);
bool			find_paths(t_context *ctx);

/**************		EXEC_ERROR_UTILS.C		**************/
void			print_error_cmd(t_context *ctx, char *argv);
char			*strjoin_and_free_s1(char *s1, char *s2);
char			*strjoin_and_free_s2(char *s1, char *s2);
bool			error_msg(t_context *ctx, char *argv);

/**************		EXEC_UTILS.C		**************/
bool			init_exec(t_node *tree, t_context *ctx, t_info *info);
bool			init_ctx(t_context *ctx);
int				ast_cmd_number(t_node *tree, int x);
void			clean_struct(t_context *ctx);
void			free_2d(char **str);

/**************		BUILT_IN.C		**************/
void			echo(char **str, int fd);
void			env(char **envp, int fd);
void			pwd(int fd);
unsigned char	ft_exit(char *code);
void			cd(t_context *ctx, char	*path);

/**************		EXEC_BUILT_IN.C		**************/
bool			exec_built_in(t_node *tree, t_context *ctx, bool flag);
bool			is_built_in(t_node *tree);

/**************		UNSET.C		**************/
char			**unset(char **envp, char *var);

/**************		EXPORT.C		**************/
char			**export(char **envp, char *var);

/**************		BUILT_IN_UTILS.C		**************/
bool			check_var_name(char *var);
bool			is_in_env(char	**envp, char *var);
char			*find_var(char *var);
int				find_len_var(char *var);
unsigned int	ft_atoui(const char *nptr);

#endif
