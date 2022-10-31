/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbily <fbily@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:59:43 by sbeylot           #+#    #+#             */
/*   Updated: 2022/10/31 18:21:53 by fbily            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <stdbool.h>
# include "../libft/includes/libft.h"

typedef enum e_type
{
	CMD,
	REDIR,
	WORD,
	PIPE,
	REDIRIN,
	REDIROUT,
	APPEND,
	HEREDOC,
	IONUMBER,
	IOFILE,
	SQUOTE,
	DQUOTE,
	NOTYPE
}				t_type;

typedef struct s_slice
{
	char	*start;
	int		len;
	int		qnbr;
	int		elem;
}				t_slice;

typedef struct s_token
{
	t_type			type;
	t_slice			location;
	struct s_token	*next;
}				t_token;

typedef struct s_node	t_node;

typedef struct s_node_cmd
{
	char		**value;
	int			cmd_len;
}				t_cmd;

typedef struct s_node_redir
{
	int			fd;
	char		*file;
}				t_redir;

typedef struct s_node_branch
{
	int			index;
	t_node		*left;
	t_node		*right;
}				t_branch;

typedef union u_data
{
	t_cmd		c;
	t_redir		r;
	t_branch	b;
}				t_data;

struct s_node
{
	t_type		type;
	t_data		data;
};

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

void	init_vars(t_pipex *pipex, char **envp, t_node *tree);
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
void	init_pipe(t_pipex *pipex);

/* --- token.c --- */
int		add_token(t_token **tokens, t_token *token);
t_token	*token_symbol(char **itr);
void	tokenizer(char *line, t_token **tokens);

/* --- token_creation.c --- */
t_token	*token_word(char **itr);
t_token	*token_single_symbol(char **itr);
t_token	*token_quoted(char **itr);
t_token	*token_append_heredoc(char **itr);

/* --- token_creation2.c --- */
t_token	*token_redir(char **itr);
t_token	*token_redir2(char **itr);
t_token	*token_redir_fd(char **itr);
t_token	*token_redir2_fd(char **itr);

/* --- token_creation_utils.c --- */
int		add_quoted_len(char **itr, t_type type);
int		add_word_len(char **itr);

/* --- token_debug.c --- */
void	debug_token_type(int c);
void	token_print(t_token *token);
char	*debug_node_type(int c);

/* --- token_utils.c --- */
int		is_whitespace(char c);
int		is_ignored(char c);
int		is_symbol(char *c);
int		is_closed(char *itr, char quote);
void	free_token(t_token **token);

/* --- token_iterator.c --- */
int		has_next(char *itr);
int		itr_is_redirection(char *c);
int		itr_is_quote(char *c);
char	peek(char *itr);
char	next(char **itr);

/* --- env_path.c --- */
int		tab_len(char **tab);
char	**split_path(char *path);
char	*get_path_env(char **envp, char *var);
char	**get_path(char **envp);
char	**copy_env(char **envp);

/* --- word_expansion.c --- */
char	*extract_word(t_token **token);
int		we_create_word(char **tab, char **envp);
char	*we_reconstruct_word(char **tab, int index);
char	*word_expansion(char **str);

/* --- word_expansion_utils.c --- */
int		dollar_inside(char *str);
int		tab_length(char **tab);
int		var_exist(char *str, char **envp);
int		word_expansion_len(char **tab);

/* --- word_expansion_utils2.c --- */
char	*ew_get_word(t_token **token, char **str);
char	*ew_get_dquote(t_token **token, char **str);
char	*ew_get_squote(t_token **token, char **str);

/* --- split_dollar.c --- */
char	**ft_dollar_malloc_tab(char const *s);
char	**ft_split_dollar(char const *s);

/* --- ast_node_cmd.c --- */
t_node	*node_cmd(t_token **token, t_node **tree);
char	**init_cmd(t_token **token);
int		cmd_length(t_token *token);

/* --- ast_node_cmd_utils.c --- */
int		is_cmd_token(t_token *token);
int		is_redirection_token(t_token *token);
int		nbr_new_argument(t_token **token);
int		update_cmd(t_token **token, t_node *tree);

/* --- ast_node_redir.c --- */
t_node	*node_redirection(t_node **tree, t_token **token);
t_node	*node_pipe(t_node **tree);
t_node	*init_redir(t_token **token);

/* --- ast_node_redir_utils.c --- */
void	init_node_redir(t_node **node);
void	assign_ionumber(t_node **node, t_token **token);
int		valid_redir(t_token *token);
void	assign_redir(t_node **node, t_token **token);

/* --- node_utils.c --- */
t_type	get_ttype(t_token **token);
char	*get_tstr(t_token **token);
size_t	get_tlen(t_token **token);
t_node	*get_cmd_node(t_node *node);
t_node	*get_last_redir(t_node *node);

/* --- clean.c --- */
void	clean_tab(char **tab, int index);
void	clean_cmd_node(t_node **node);
void	clean_tree(t_node **tree);

/* --- scanning.c --- */
void	next_token(t_token **token);
void	eat_token(t_token **token);

/* --- parsing.c --- */
t_node	*parsing(char *line);
t_node	*parse_redir(t_token **token);
t_node	*parse_pipe(t_token **token);

/* --- main (futur clean.c) --- */
t_node	*node_pipe(t_node **tree);

/* --- debug_print.c --- */
void	print_node_cmd(t_node *node);
void	print_node_redir(t_node *node);
void	printtab(int ntab);
void	print_tree_recur(t_node *tree, int level);
void	tree_print(t_node *tree);

/* --- signal.c --- */
void	init_signal(void);

#endif
