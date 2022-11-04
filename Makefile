# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbily <fbily@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/19 14:13:03 by sbeylot           #+#    #+#              #
#    Updated: 2022/11/04 10:34:29 by sbeylot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# BASE INFO
NAME		=	minishell	
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror 
# SRCS
SRCS_NAME	=	main_flo.c\
				token.c\
				token_creation.c\
				token_creation2.c\
				token_creation_utils.c\
				token_debug.c\
				token_utils.c\
				token_iterator.c\
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
				exec_cmd_utils.c

SRCS_DIR	=	srcs/
SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_NAME))

# OBJS
OBJS_DIR	=	objs/
OBJS		=	$(SRCS_NAME:%.c=$(OBJS_DIR)%.o)

#LIBFT
LIBFT_INC	= -L./libft
LIBFT_A		=	-lft
LIBFT		=	$(addprefix $(LIBFT_INC) , $(LIBFT_A))

#HEADER
HEADER		=	./includes/minishell.h
HEADER_INC	=	-I./includes	
HEADER_INC_LIBFT	=	-I./libft/includes
#READLINE
READLINE	=	-lreadline

RED 		=	\033[0;31m
GREEN 		=	\033[0;32m
NONE 		=	\033[0m

all: info compile_libft $(NAME)
	@echo "\t\t[ $(GREEN)✓$(NONE) ] $(GREEN)$(NAME)$(NONE) ready!"

compile_libft:
	@make -C ./libft --no-print-directory

$(NAME): $(OBJS) $(HEADER)
	@$(CC) $(CFLAGS) $(HEADER_INC) $(HEADER_INC_LIBFT) $(OBJS) $(READLINE) $(LIBFT) -o $(NAME)

malloc_test: compile_libft $(OBJS) $(HEADER)
	$clang $(CFLAGS) -g -fsanitize=undefined -rdynamic -o $@ $(OBJS) $(HEADER_INC) $(HEADER_INC_LIBFT) $(LIBFT) $(READLINE) -L. -lmallocator
   

run: all
	@./$(NAME)

debug: info compile_libft 
	@$(CC) $(HEADER_INC) $(HEADER_INC_LIBFT) $(SRCS) -o $(NAME) $(READLINE) $(LIBFT) -g3 -fsanitize=address 
	@echo "\t\t[ $(GREEN)✓$(NONE) ] $(GREEN)$(NAME)$(NONE) for GDB ready!"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER)
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(HEADER_INC) $(HEADER_INC_LIBFT) -c $< -o $@

clean:
	@rm -rf $(OBJS_DIR)
	@echo "\t\t[ $(RED)✗$(NONE) ] objs/ directory"

fclean: clean
	@rm -f $(NAME)
	@rm -rf gmon.out
	@echo "\t\t[ $(GREEN)✓$(NONE) ] Project $(GREEN)$(NAME)$(NONE) clean"

re: fclean all

.PHONY: all clean fclean re info header



info: header

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
