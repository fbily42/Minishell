# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbily <fbily@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 21:41:49 by fbily             #+#    #+#              #
#    Updated: 2022/11/11 21:56:09 by fbily            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a 

SRC_PATH = ./srcs/
SRC =			ft_atoi.c\
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

SRCS = $(addprefix ${SRC_PATH}, ${SRC})

OBJ_PATH	= obj/
OBJ = ${SRC:.c=.o}

OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

INC = -I./includes/

DEPS = $(addprefix ${OBJ_PATH}, ${SRC:.c=.d})

CC = cc

CFLAGS = -Wall -Wextra -Werror -MMD -MP

RED 		=	\033[0;31m
GREEN 		=	\033[0;32m
NONE 		=	\033[0m

all: $(NAME)

${NAME} : ${OBJS}
	@ar rc ${NAME} $^
	@echo "\t\t[ $(GREEN)✓$(NONE) ] Libft ready!$(NONE)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p ${OBJ_PATH}
	@${CC} ${CFLAGS} ${INC} -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH)
	@echo "\t\t[ $(RED)✗$(NONE) ] libft/$(OBJ_PATH) directory"

fclean: clean
	@rm -f	$(NAME)
	@echo "\t\t[ $(RED)✗$(NONE) ] libft/$(NAME) library"

re:			fclean all

-include ${DEPS}

.SECONDARY: ${OBJ_PATH} ${OBJ} ${OBJS}

.PHONY: all clean fclean re
