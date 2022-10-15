# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fstitou <fstitou@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/20 01:09:59 by fahd              #+#    #+#              #
#    Updated: 2022/10/15 04:00:01 by fstitou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
NAME_BONUS = 

SRC = philo.c init.c routine.c tools.c
		
SRC_BONUS = 


OBJ =  philo.o init.o routine.o tools.o

OBJ_BONUS = 

all : $(NAME)

$(NAME):
	
	@gcc -Wall -Wextra -Werror $(SRC) -o $(NAME) -pthread -g -fsanitize=thread
	@echo "👍👍👍"

$(NAME_BONUS) : 
	@gcc -Wall -Wextra -Werror -g $(SRC_BONUS) -o $(NAME_BONUS)
	@echo "🎁🎁🎁"

bonus: $(NAME_BONUS)

clean :
 
	@rm -f $(OBJ) $(OBJ_BONUS)
	@echo "🚮🚮🚮"

fclean : clean
	@rm -f $(NAME) $(NAME_BONUS)
	@echo "🗑️ 🗑️ 🗑️"

re : fclean all