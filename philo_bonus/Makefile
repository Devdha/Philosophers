# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dha <dha@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/09 17:56:16 by dha               #+#    #+#              #
#    Updated: 2022/04/20 20:27:36 by dha              ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -rf
NAME = philo_bonus

SRCS = main_bonus.c \
		error_bonus.c \
		util0_bonus.c \
		util1_bonus.c \
		util2_bonus.c \
		init_bonus.c \
		dining_bonus.c \
		scanner_bonus.c
INCS = philo_bonus.h
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

re:
	@make fclean all

.PHONY : all clean fclean re