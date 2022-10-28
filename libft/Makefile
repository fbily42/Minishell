CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -f
NAME		=	libft.a 

SRCS_DIR	=	srcs/
SRCS_NAMES	=	ft_atoi.c\
	 			ft_bzero.c\
				ft_calloc.c\
				ft_isalnum.c\
				ft_isalpha.c\
				ft_isascii.c\
				ft_isdigit.c\
				ft_isprint.c\
				ft_itoa.c\
				ft_memchr.c\
				ft_memcmp.c\
				ft_memcpy.c\
				ft_memmove.c\
				ft_memset.c\
				ft_putchar_fd.c\
				ft_putendl_fd.c\
				ft_putstr_fd.c\
				ft_putnbr_fd.c\
				ft_split.c\
				ft_strchr.c\
				ft_strdup.c\
				ft_striteri.c\
				ft_strjoin.c\
				ft_strlcat.c\
				ft_strlcpy.c\
				ft_strlen.c\
				ft_strmapi.c\
				ft_strncmp.c\
				ft_strnstr.c\
				ft_strrchr.c\
				ft_strtrim.c\
				ft_substr.c\
				ft_tolower.c\
				ft_toupper.c\
				ft_lstnew.c\
				ft_lstadd_front.c\
				ft_lstsize.c\
				ft_lstlast.c\
				ft_lstadd_back.c\
				ft_lstdelone.c\
				ft_lstclear.c\
				ft_lstiter.c\
				ft_lstmap.c\
				ft_printf.c\
				do_cs_to_str.c\
				do_diu_to_str.c\
				do_p_to_str.c\
				do_x_to_str.c\
				get_next_line.c\
				get_next_line_utils.c\
				ft_split_utils.c

SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_NAMES))
OBJS_DIR	=	objs/
OBJS		=	$(SRCS_NAMES:%.c=$(OBJS_DIR)%.o)

HDR_NAMES	=	libft.h
HDR_DIR		=	includes/
HDRS		=	$(addprefix $(HDR_DIR), $(HDR_NAMES))

HDR_INC 	=	$(addprefix -I./, $(HDR_DIR))

RED 		=	\033[0;31m
GREEN 		=	\033[0;32m
NONE 		=	\033[0m

all: creation $(NAME)
	@echo "\t\t[ $(GREEN)✓$(NONE) ] Libft ready!$(NONE)"

creation:
	@echo "\t\t[...] Libft creation..."

cleaning:
	@echo "\t\tCleaning libft directory..."

$(NAME): $(OBJS) $(HDRS)
	@ar rcs $@ $(OBJS)
	@echo "\t\t[ $(GREEN)✓$(NONE) ] libft/libft.a"

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(HDR_INC) -c $< -o $@

clean: 
	@rm -rf $(OBJS_DIR)
	@echo "\t\t[ $(RED)✗$(NONE) ] libft/$(OBJS_DIR) directory"

fclean:		clean
	@rm -f	$(NAME)
	@echo "\t\t[ $(RED)✗$(NONE) ] libft/$(NAME) library"

re:			fclean all

.PHONY: all clean fclean re
