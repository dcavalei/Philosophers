# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcavalei <dcavalei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/21 12:29:07 by dcavalei          #+#    #+#              #
#    Updated: 2021/06/29 12:18:43 by dcavalei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= $(shell find src -type f -name "*.c")
HDR			= $(shell find inc -type f -name "*.h")
OBJ			= $(SRC:.c=.o)
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g -pthread
NAME		= philo

GREEN		= \033[0;32m
NC			= \033[0m

all:		$(NAME)

.c.o:
			@echo "Creating object: $@"
			@$(CC) $(CFLAGS) -Iinc -c $< -o $@

$(NAME):	$(OBJ) $(HDR)
			@$(CC) -o $(NAME) $(CFLAGS) -Iinc $(OBJ)

clean:
			@echo "${GREEN}Removing object files...${NC}"
			@rm -f $(OBJ)

fclean:		clean
			@echo "${GREEN}Removing executable file:${NC} $(NAME)"
			@rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
