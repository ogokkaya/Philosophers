NAME = philo
CC = cc -Wall -Wextra -Werror 
SOURCE = main.c\
		 utils.c 


OBJ = $(SOURCE:.c=.o)

$(NAME): $(OBJ)
		@$(CC) $(OBJ) -o $(NAME)
all : $(NAME)

.c.o:
	$(CC) -c -o $(NAME)

clean:
	@rm -rf *.o
	
f:	fclean

fclean:
	@rm -rf $(NAME)

re: fclean all

.PHONY: re fclean clean all