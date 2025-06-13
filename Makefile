CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = philosophers

UTILS_DIR = utils
SRC_DIR = src
OBJ_DIR = obj
INCS = -I includes

SRC = philosophers.c parsing.c init_table.c \
	start_dinner.c synchro_dinner.c print.c \
	routine.c
UTILS = utils.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o) $(UTILS:.c=.o))

GREEN = \033[0;92m
BLUE = \033[0;94m
CYAN = \033[0;96m
YELLOW = \033[0;93m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN) Compilation of $(NAME) completed!$(BLUE)"

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
