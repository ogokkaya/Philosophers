NAME = philo
CC = cc -Wall -Wextra -Werror
SOURCE = utils.c main.c input_control.c create.c operating_philo.c created_destroy.c time.c die_check_and_write.c

OBJ = $(SOURCE:.c=.o)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME)
all: $(NAME)


c: clean
clean:
	@rm -rf *.o

f: fclean
fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: re fclean clean all f c