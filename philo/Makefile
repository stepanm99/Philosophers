NAME = philo

SRC = main.c arg_parsing.c data.c deployment_utils.c error.c time.c \
	deployment_of_philos.c grim_reaper.c philosopher.c \
	philosopher_utils.c philosopher_fork_handling.c memory_cleanup.c

CC = cc
FLAGS = -Wall -Wextra -Werror -g
DFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -static-libsan
PRINT_FLAG = -D PRINT_NUMBER_OF_EATS=1

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking $@"
	@$(CC) $(OBJ) $(DFLAGS) -o $(NAME)
	@echo "Done!"

%.o: %.c
	@echo "Compiling $<"
	@$(CC) $(DFLAGS) $(PRINT_FLAG) -c $< -o $@

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
