NAME := philo

SRC :=	src/main.c \
		src/error.c \
		src/setup.c \
		src/sim_init.c \
		src/sim.c \
		src/sim_god.c \
		src/sim_utils.c \
		src/utils/utils1.c \
		src/utils/utils2.c \

OBJ := $(SRC:.c=.o)

CC := cc

CFLAGS := -Wall -Wextra -Werror -pthread #-g -fsanitize=thread

GREEN := \033[0;32m
CYAN := \033[0;36m
RED := \033[0;31m
NC := \033[0m

all: $(OBJ) $(NAME)

$(OBJ): %.o: %.c
		@echo "$(CYAN)	Compiling $@...$(NC)"
		@$(CC) $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
		@echo "$(GREEN)\n###########################################$(NC)"
		@echo "$(GREEN)	$(NAME) is ready!$(NC)"
		@echo "$(GREEN)###########################################$(NC)"

clean:
		@echo "$(CYAN)\n# Cleaning object files...\n$(NC)"
		rm -f $(OBJ)
		@echo "$(GREEN)\n###########################################$(NC)"
		@echo "$(GREEN)	$(NAME) object files cleaned!$(NC)"
		@echo "$(GREEN)###########################################$(NC)"

fclean: clean
		@echo "$(CYAN)\n# Cleaning $(NAME) ...\n$(NC)"
		rm -f $(NAME)
		@echo "$(GREEN)\n###########################################$(NC)"
		@echo "$(GREEN)	$(NAME) cleaned!$(NC)"
		@echo "$(GREEN)###########################################$(NC)"

re: fclean all

.PHONY: all clean fclean re