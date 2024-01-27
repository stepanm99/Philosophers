NAME = philo

SRC = main.c arg_parsing.c data.c debug.c error.c time.c \
	deployment_of_philos.c grim_reaper.c philosopher.c \
	philosopher_utils.c

CC = cc
FLAGS = -Wall -Wextra -Werror -g
DFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -static-libsan

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking $@"
	@$(CC) $(OBJ) $(FLAGS) -o $(NAME)
	@echo "Done!"

%.o: %.c
	@echo "Compiling $<"
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

test:
	@gcc test.c -o test
	@./test

rtest:
	@./test

.PHONY: all clean fclean re
