NAME = philo

SRC = main.c arg_parsing.c data.c error.c grim_reaper_utils.c time.c \
	deployment_of_philos.c grim_reaper.c philosopher.c \
	philosopher_utils.c philosopher_fork_handling.c memory_cleanup.c

CC = cc
FLAGS = -Wall -Wextra -Werror -O # -g -fsanitize=address -static-libsan
PRINT_FLAG = -D PRINT_NUMBER_OF_EATS=1

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking $@"
	@$(CC) $(OBJ) $(FLAGS) -o $(NAME)
	@echo "Done!"

%.o: %.c
	@echo "Compiling $<"
	@$(CC) $(FLAGS) $(PRINT_FLAG) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
