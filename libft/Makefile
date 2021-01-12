# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/12 14:42:41 by rkirszba          #+#    #+#              #
#    Updated: 2021/01/12 20:13:07 by rkirszba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a


CC		= gcc

CFLAGS	= -Wall\
		  -Wextra\
		  -Werror

#For developping purposes:
# CFLAGS 	+= -fsanitize=address,undefined\
				   -g3

SRCS_DIR		= srcs/
SRCS_NAMES		= ft_strlen.c\
				  ft_list_new.c\
				  ft_list_append.c\
				  ft_list_prepend.c\
				  ft_list_free.c\
				  ft_btree_new.c\
				  ft_btree_insert.c\
				  ft_btree_inorder.c


INCS_DIR		= includes/
INCS_NAMES		= libft.h

OBJS_DIR		= objs/
$(shell mkdir -p $(OBJS_DIR))


SRCS	= $(addprefix $(SRCS_DIR), $(SRCS_NAMES))
INCS	= $(addprefix $(INCS_DIR), $(INCS_NAMES))
OBJS	= $(SRCS:$(SRCS_DIR)%.c=$(OBJS_DIR)%.o)



all: $(NAME)

$(NAME): $(OBJS)
	ar rc $@ $^
	ranlib $@
	@echo "made libft"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(INCS) Makefile
	$(CC) $(CFLAGS) -o $@ -c $< -I./$(INCS_DIR)

clean:
	$(shell rm -rf $(OBJS))
	$(shell rm -rf $(OBJS_DIR))

fclean: clean
	$(shell rm -rf $(NAME))

re: fclean
	make all

.PHONY: all clean fclean re