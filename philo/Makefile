NAME = philo

SRC = main.c

CC = cc
FLAGS = -Wall -Wextra -Werror
DFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -static-libsan

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking $@"
	@$(CC) $(OBJ) $(FLAGS) -o $(NAME)
	@echo "Done!"

%.o: %.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re