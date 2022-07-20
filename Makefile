# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fahd <fahd@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/20 01:09:59 by fahd              #+#    #+#              #
#    Updated: 2022/07/20 01:10:02 by fahd             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
NAME_BONUS = 

SRC = philo.c init.c
		
SRC_BONUS = 


OBJ =  philo.o init.o

OBJ_BONUS = 

all : $(NAME)

$(NAME):
	
	@gcc -Wall -Wextra -Werror $(SRC) -o $(NAME) -pthread -g -fsanitize=address
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