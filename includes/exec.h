/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:35:31 by fbily             #+#    #+#             */
/*   Updated: 2022/11/21 10:22:04 by sbeylot          ###   ########.fr       */
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
void			minishell(t_node *tree, t_context *ctx);
char			**handle_mini_envp(t_context *ctx);

/**************		EXEC.C		**************/
int				exec_pipe(t_node *tree, t_context *ctx, int *p_int);
int				exec_node(t_node *tree, t_context *ctx, int *p_int);
int				exec_cmd(t_node *tree, t_context *ctx, int *p_int);
void			child(t_node *tree, t_context *ctx);
void			exec(t_node *tree, t_context *ctx);

/**************		WAIT.C		**************/
void			wait_exit_code(t_context *ctx, t_info info);

/**************		EXEC_REDIR_UTILS.C		**************/
bool			open_file_out(t_context *ctx, t_node *tree, bool flag);
bool			update_redir(t_node *tree, t_context *ctx);
bool			open_file_in(t_context *ctx, t_node *tree);
bool			redir_out(t_node *tree, t_context *ctx);
bool			redir_in(t_node *tree, t_context *ctx);

/**************		HERE_DOC_AND_PATH.C		**************/
int				heredoc(t_node	*node, t_context *ctx);
bool			create_paths(t_context *ctx);
bool			find_paths(t_context *ctx);
void			ft_close(t_context *ctx);

/**************		EXEC_CMD_UTILS.C		**************/
bool			check_cmd_with_path(t_node *tree, t_context *ctx);
void			check_exceptions(char *cmd, t_context *ctx);
bool			check_dot_slash(char *cmd, t_context *ctx);
void			execute_cmd(t_node *tree, t_context *ctx);
bool			find_cmd(t_node *tree, t_context *ctx);

/**************		EXEC_ERROR_UTILS.C		**************/
void			exit_and_clean(t_context *ctx, unsigned char code);
void			print_error_cmd(t_context *ctx, t_node *tree);
char			*strjoin_and_free_s1(char *s1, char *s2);
char			*strjoin_and_free_s2(char *s1, char *s2);
void			error_malloc(t_context *ctx);

/**************		EXEC_UTILS.C		**************/
bool			init_exec(t_node *tree, t_context *ctx, t_info *info);
int				ast_cmd_number(t_node *tree, int x);
void			clean_struct(t_context *ctx);
bool			init_ctx(t_context *ctx);
void			free_2d(char **str);

/**************		BUILT_IN.C		**************/
int				check_option_echo(char	**str, int *flag);
bool			cd(t_context *ctx, char	*path);
void			echo(char **str, int fd);
void			env(char **envp, int fd);
void			pwd(int fd);

/**************		BUILT_IN_2.C		**************/
void			check_arg_exit(t_context *ctx, char *str, long long *exit_code);
void			ft_exit(t_context *ctx, char **args);

/**************		EXEC_BUILT_IN.C		**************/
bool			exec_unset_export_exit(t_node *tree, t_context *ctx);
bool			exec_built_in(t_node *tree, t_context *ctx, int fd);
bool			execute_cd(t_node *tree, t_context *ctx);
bool			is_built_in(t_node *tree);

/**************		UNSET.C		**************/
char			**unset(char **envp, char *var, t_context *ctx);
void			export_not_valid(t_context *ctx);
void			env_2(char **envp, int fd);

/**************		EXPORT.C		**************/
void			sort_and_print_env(t_context *ctx);
char			**export(char **envp, char *var, t_context *ctx);

/**************		BUILT_IN_UTILS.C		**************/
bool			is_in_env(char	**envp, char *var);
long long		ft_atoll_capped(const char *nptr, int *flag);
bool			check_var_name(char *var);
int				find_len_var(char *var);
char			*find_var(char *var);

#endif
