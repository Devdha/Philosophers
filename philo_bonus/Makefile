# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 17:56:16 by dha               #+#    #+#              #
#    Updated: 2022/04/13 15:46:11 by dha              ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC = cc
# CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -rf
NAME = philo

SRCS = main.c \
		error.c \
		util.c \
		util2.c \
		init.c \
		dining.c \
		scanner.c
INCS = philo.h
OBJ_DIR = ./obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

%o: %c
	$(CC) -c $(CFLAGS)$< -o $(<:.c=.o) -I.

$(NAME): $(OBJS) $(INCS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@
	@printf "💡 Make $(NAME) Done\n"

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -g

all: $(NAME)

clean :
	@$(RM) $(OBJ_DIR)
	@echo "🗑 Remove $(NAME)'s OBJs Done"

fclean : clean
	@$(RM) $(NAME)
	@echo "🗑 Remove $(NAME) Done"

re: fclean all

.PHONY : all clean fclean re