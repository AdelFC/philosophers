CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo

UTILS_DIR = utils
SRC_DIR = src
OBJ_DIR = obj
INCS = -I includes

SRC = philosophers.c parsing.c init_table.c \
	start_dinner.c wait_start.c \
	routine.c monitor.c
UTILS = utils.c helpers.c print.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o) $(UTILS:.c=.o))

GREEN = \033[0;92m
BOLD_GREEN = \033[1;92m
CYAN = \033[0;96m
YELLOW = \033[0;93m
BLUE = \033[0;34m
BOLD_BLUE = \033[1;34m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(BOLD_GREEN)Compilation of $(NAME) completed!$(BOLD_GREEN)"
	@echo ""
	@echo "$(BLUE)----------------------------------------\033[0m"
	@echo "$(BOLD_BLUE)USAGE :\033[0m"
	@echo "$(BLUE)  ./philo philo_nbr time_to_die time_to_eat time_to_sleep [nbr_max_meals]\033[0m"
	@echo ""
	@echo "$(BOLD_BLUE)EXAMPLE :\033[0m"
	@echo "$(BLUE)  ./philo 5 800 200 200 3\033[0m"
	@echo "$(BLUE)----------------------------------------\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@
	@echo "$(CYAN)Compiled: $<$(BLUE)"

$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@
	@echo "$(CYAN)Compiled: $<$(BLUE)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)Cleaned object files.$(BLUE)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(YELLOW)Removed $(NAME) and compiled files.$(BLUE)"

re: fclean all

.PHONY: all clean fclean re
