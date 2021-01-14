# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/12 16:16:50 by rkirszba          #+#    #+#              #
#    Updated: 2021/01/14 19:17:36 by rkirszba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME_NM		= ft_nm
NAME_OT		= ft_otool


CC		= gcc

CFLAGS	= -Wall\
		  -Wextra\
		  -Werror

#For developping purposes:
# CFLAGS 	+= -fsanitize=address,undefined\
				   -g3



SRCS_DIR_NM		= srcs_nm/
SRCS_DIR_OT		= srcs_otool/

SRCS_NAMES_NM	= ft_nm.c\
				  args_parser.c\
				  files_process.c\
				  handlers.c\
				  security.c\
				  symbols_get.c\
				  errors.c

SRCS_NAMES_OT	= ft_otool.c

OBJS_DIR_NM		= objs_nm/
OBJS_DIR_OT		= objs_otool/

INCS_DIR_NM		= includes_nm/
INCS_DIR_OT		= includes_ot/

INCS_NAMES_NM	= ft_nm.h
INCS_NAMES_OT	= ft_otool.h

SRCS_NM	= $(addprefix $(SRCS_DIR_NM), $(SRCS_NAMES_NM))
INCS_NM	= $(addprefix $(INCS_DIR_NM), $(INCS_NAMES_NM))
OBJS_NM	= $(SRCS_NM:$(SRCS_DIR_NM)%.c=$(OBJS_DIR_NM)%.o)

SRCS_OT	= $(addprefix $(SRCS_DIR_OT), $(SRCS_NAMES_OT))
INCS_OT	= $(addprefix $(INCS_DIR_OT), $(INCS_NAMES_OT))
OBJS_OT	= $(SRCS_OT:$(SRCS_DIR_OT)%.c=$(OBJS_DIR_OT)%.o)


LIB_DIR			= libft/
LIB_NAME		= libft.a
LIB				= $(addprefix $(LIB_DIR), $(LIB_NAME))
LIB_INCS_DIR	= $(addprefix $(LIB_DIR), includes/)


all: $(NAME_NM) $(NAME_OT)

$(NAME_NM): $(OBJS_NM) $(LIB)
	$(CC) $(CFLAGS) -o $@ $^

$(NAME_OT): $(OBJS_OT) $(LIB)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJS_DIR_NM)%.o: $(SRCS_DIR_NM)%.c $(INCS_NM) Makefile
	$(shell mkdir -p $(OBJS_DIR_NM))
	$(CC) $(CFLAGS) -o $@ -c $< -I./$(INCS_DIR_NM) -I./$(LIB_INCS_DIR)

$(OBJS_DIR_OT)%.o: $(SRCS_DIR_OT)%.c $(INCS_OT) Makefile
	$(shell mkdir -p $(OBJS_DIR_OT))
	$(CC) $(CFLAGS) -o $@ -c $< -I./$(INCS_DIR_OT) -I./$(LIB_INCS_DIR)

$(LIB): FORCE
	@make -C $(LIB_DIR)

clean: clean_nm clean_ot
	@make clean -C $(LIB_DIR)

clean_nm:
	@rm -rf $(OBJS_NM)
	@rm -rf $(OBJS_DIR_NM)

clean_ot:
	@rm -rf $(OBJS_OT)
	@rm -rf $(OBJS_DIR_OT)

fclean: fclean_nm fclean_ot
	@make fclean -C $(LIB_DIR)

fclean_nm: clean_nm
	@rm -rf $(NAME_NM)

fclean_ot: clean_ot
	@rm -rf $(NAME_OT)

re: fclean
	make all


.PHONY: all clean fclean re clean_nm clean_ot fclean_nm fclean_ot

FORCE: