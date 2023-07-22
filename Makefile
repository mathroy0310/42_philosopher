# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maroy <maroy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/18 17:31:16 by maroy             #+#    #+#              #
#    Updated: 2023/07/21 20:36:03 by maroy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= philo

HEADER			= philo.h 

SRCPATH_DIR		= src/
SRCPATH_SRC		= philo.c utils.c inits.c run.c observer.c
SRCPATH			= $(addprefix $(SRCPATH_DIR)/, $(SRCPATH_SRC))
OBJ 			= $(patsubst $(SRCPATH_DIR)%.c,obj/%.o,$(SRCPATH))

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -pthread -Ofast #-g #-fsanitize=thread
RM			= rm -rf

obj/%.o: $(SRCPATH_DIR)%.c  $(HEADER)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJ) 
			@$(CC) $(CFLAGS) $(OBJ)  -o $(NAME)
			@echo "$(GREEN)$(NAME) created !$(DEFAULT)"

all:		$(NAME)

clean:
			@$(RM) $(OBJ)
			@echo	"$(YELLOW)Obejct files deleted!$(DEFAULT)"

fclean:		clean
			@$(RM) $(NAME)
			@echo	"$(RED)All deleted!$(DEFAULT)"  

re:			fclean all

norm:
			@echo "$(DARKGRAY)norminette! $(DEFAULT)"
			norminette $(SRCPATH) $(HEADER)

.PHONY:		all clean fclean re norm

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DARKGRAY= \033[1;30m
DEFAULT = \033[1;30m
