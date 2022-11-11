/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbeylot <sbeylot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 08:43:36 by sbeylot           #+#    #+#             */
/*   Updated: 2022/11/11 12:54:15 by sbeylot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef enum e_type
{
	CMD,
	ARG,
	REDIR,
	WORD,
	PIPE,
	REDIRIN,
	REDIROUT,
	APPEND,
	HEREDOC,
	IONUMBER,
	IOFILE,
	DOLLAR,
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

typedef struct s_context
{
	int		pipe[2];
	int		nb_cmd;
	char	**envp;
	char	**my_paths;
	char	*error;
	char	*cmd;
	t_node	*root;
	int		*pchild;
}				t_context;

/* --- token.c --- */
int		add_token(t_token **tokens, t_token *token, t_context *ctx);
t_token	*token_symbol(char **itr);
void	tokenizer(char *line, t_token **tokens, t_context *ctx);

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
int		add_dollar_len(char **itr);
t_token	*init_token(char **itr, t_type type);

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
char	*extract_delimiter(t_token **token, t_context *ctx);
char	*extract_word(t_token **token, int option, t_context *ctx);
int		we_create_word(char **tab, int i, t_context *ctx);
char	*we_reconstruct_word(char **tab, int index);
char	*word_expansion(char **str, t_context *ctx);

/* --- word_expansion_utils.c --- */
int		dollar_inside(char *str);
int		tab_length(char **tab);
int		var_exist(char *str, char **envp);
int		word_expansion_len(char **tab);

/* --- word_expansion_utils2.c --- */
char	*ew_get_word(t_token **token, char **str, int option, t_context *ctx);
char	*ew_get_dquote(t_token **token, char **str, int option, t_context *ctx);
char	*ew_get_squote(t_token **token, char **str);

/* --- split_dollar.c --- */
char	**ft_dollar_malloc_tab(char const *s);
char	**ft_split_dollar(char const *s);

/* --- ast_node_cmd.c --- */
t_node	*node_arg(t_token **token, t_context *ctx);
t_node	*node_pipe(t_node **tree, t_token **token, t_context *ctx);
t_node	*node_redirection(t_token **token, t_context *ctx);
char	**init_cmd(t_token **token, t_context *ctx);
int		cmd_length(t_token *token);

/* --- ast_node_cmd_utils.c --- */
int		is_cmd_token(t_token *token);
int		is_redirection_token(t_token *token);
int		nbr_new_argument(t_token **token);
int		update_cmd(t_token **token, t_node *tree, t_context *ctx);

/* --- ast_node_redir.c --- */

/* --- ast_node_redir_utils.c --- */
t_node	*init_redir(t_token **token, t_context *ctx);
void	init_node_redir(t_node **node);
void	assign_ionumber(t_node **node, t_token **token);
int		valid_redir(t_token *token);
void	assign_redir(t_node **node, t_token **token, t_context *ctx);

/* --- node_utils.c --- */
t_type	get_ttype(t_token **token);
char	*get_tstr(t_token **token);
size_t	get_tlen(t_token **token);
t_node	*get_last_redir(t_node *node);
t_node	*get_last_pipe(t_node *node);

/* --- clean.c --- */
void	clean_tab(char **tab, int index);
void	clean_cmd_node(t_node **node);
void	clean_tree(t_node **tree);

/* --- scanning.c --- */
void	next_token(t_token **token);
void	eat_token(t_token **token);

/* --- parsing.c --- */
t_node	*parsing(char *line, t_context *ctx);
t_node	*parse_redir(t_token **token, t_context *ctx);
t_node	*parse_pipe(t_token **token, t_context *ctx);
t_node	*parse_cmd(t_token **token, t_context *ctx);

/* --- main (futur clean.c) --- */

/* --- debug_print.c --- */
void	print_node_cmd(t_node *node);
void	print_node_redir(t_node *node);
void	printtab(int ntab);
void	tree_print(t_node *tree);
void	new_print_tree_recur(t_node *tree, int level);

/* --- signal.c --- */
void	init_signal(void);
void	init_signal_child(void);

/* --- error.c --- */
int	print_error_token(void);
int	syntax_error_newline(void);
int	syntax_error_redir_token(t_token *token);
int	syntax_error_pipe(void);
int	error_token(t_token **token, char **itr);

/* --- buildin_pwd.c --- */
void	buildin_pwd(void);
t_token *token_delim(char **itr);


#endif
