NAME = philo_bonus
NAME_BONUS = 

SRC = philo_bonus.c init_bonus.c
		
SRC_BONUS = 


OBJ =  philo.o init.o

OBJ_BONUS = 

all : $(NAME)

$(NAME):
	
	@gcc -Wall -Wextra -Werror $(SRC) -o $(NAME) -pthread -g 	
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