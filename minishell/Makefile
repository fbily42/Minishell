# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbily <fbily@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/19 14:13:03 by sbeylot           #+#    #+#              #
#    Updated: 2022/11/18 23:31:05 by fbily            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# BASE INFO
NAME		=	minishell	
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -MMD -MP
# SRCS
SRCS_NAME	=	main.c\
				token.c\
				token_creation.c\
				token_creation2.c\
				token_creation_utils.c\
				token_debug.c\
				token_utils.c\
				token_iterator.c\
				token_error.c\
				env_path.c\
				word_expansion.c\
				word_expansion_utils.c\
				word_expansion_utils2.c\
				split_dollar.c\
				ast_node_cmd.c\
				ast_node_cmd_utils.c\
				ast_node_redir_utils.c\
				node_utils.c\
				clean.c\
				debug_print.c\
				scanning.c\
				parsing.c\
				signal.c\
				exec.c\
				exec_utils.c\
				exec_redir_utils.c\
				exec_error_utils.c\
				exec_cmd_utils.c\
				here_doc_and_path.c\
				built_in.c\
				built_in_2.c\
				exec_built_in.c\
				built_in_utils.c\
				unset.c\
				export.c\
				export_2.c\
				wait.c

SRCS_DIR	=	srcs/
SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_NAME))

# OBJS
OBJS_DIR	=	objs/
OBJ 		= ${SRCS_NAME:.c=.o}
OBJS		= $(addprefix $(OBJS_DIR), $(OBJ))

#LIBFT
LIBFT_INC	= -L./libft
LIBFT_A		=	-lft
LIBFT		=	$(addprefix $(LIBFT_INC) , $(LIBFT_A))

#HEADER
HEADER_INC	=	-I./includes/
HEADER_INC_LIBFT	=	-I./libft/includes/
#READLINE
READLINE	=	-lreadline

DEPS		=	$(addprefix $(OBJS_DIR), $(SRCS_NAME:.c=.d))

RED 		=	\033[0;31m
GREEN 		=	\033[0;32m
NONE 		=	\033[0m

all: $(NAME)

$(NAME): $(OBJS)
	make --no-print-directory header
	@make -C ./libft --no-print-directory
	@$(CC) $(CFLAGS) $(OBJS) $(READLINE) $(LIBFT) -o $(NAME)
	@echo "\t\t[ $(GREEN)✓$(NONE) ] $(GREEN)$(NAME)$(NONE) ready!"

run: all
	@./$(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c 
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(HEADER_INC) $(HEADER_INC_LIBFT) -o $@ -c $<

clean:
	@rm -rf $(OBJS_DIR)
	@echo "\t\t[ $(RED)✗$(NONE) ] objs/ directory"

fclean: clean
	@make --no-print-directory fclean -C ./libft
	@rm -f $(NAME)
	@echo "\t\t[ $(GREEN)✓$(NONE) ] Project $(GREEN)$(NAME)$(NONE) clean"

re: fclean all

.PHONY: all clean fclean re header

-include ${DEPS}

.SECONDARY: ${OBJS_DIR} ${OBJS} ${OBJ}

define HEADER 

    ███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     
    ████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     
    ██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     
    ██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     
    ██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗
    ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝

endef
export HEADER

header:
	@clear
	@echo "$$HEADER"
