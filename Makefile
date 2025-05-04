#--------------- CONFIG ----------------
NAME = ircserv
NAME_BOT = ircbot

CC = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRC_DIR = sources
SRC_DIR_BOT = sources/Bot
OBJ_DIR = objects
OBJ_DIR_BOT = objects/Bot

SRC = $(shell find $(SRC_DIR) -type f -name "*.cpp" ! -path "$(SRC_DIR_BOT)/*" | sed 's|$(SRC_DIR)/||')
SRC_BOT = $(shell find $(SRC_DIR_BOT) -type f -name "*.cpp" | sed 's|$(SRC_DIR_BOT)/||')
	
OBJ = $(SRC:%.cpp=$(OBJ_DIR)/%.o)
OBJ_BOT = $(SRC_BOT:%.cpp=$(OBJ_DIR_BOT)/%.o)

TOTAL := $(words $(SRC))

NC = \033[0m
RED = \033[31m
ORANGE = \033[33m
GREEN = \033[92m
BLUE = \033[34m

#--------------- RULES ----------------

$(OBJ_DIR_BOT)/%.o: $(SRC_DIR_BOT)/%.cpp
	@mkdir -p $(@D)
	$(CC) -c $(CXXFLAGS) -o $@ $<
	@echo "$(GREEN)[OK]$(NC)\t"$@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) -c $(CXXFLAGS) -o $@ $<
	@COMPILED=$$(find $(OBJ_DIR) -type f -name "*.o" ! -path "$(OBJ_DIR_BOT)/*" | wc -l); \
	PERCENT=$$(echo "scale=2; $$COMPILED / $(TOTAL) * 100" | bc); \
	printf "\r$(BLUE)Compiling... %d%%$(NC)" $$(printf "%.0f" $$PERCENT)
	#@echo "$(GREEN)[OK]$(NC)\t"$@

$(NAME): $(OBJ)
	@$(CC) $(CXXFLAGS) $(OBJ) -o $(NAME)
	@echo "\n------------------------------"
	@echo "$(ORANGE)$(NAME)$(NC) ready to use\n"

$(NAME_BOT): $(OBJ_BOT)
	@$(CC) $(CXXFLAGS) $(OBJ_BOT) -o $(NAME_BOT)
	@echo "\n------------------------------"
	@echo "$(ORANGE)$(NAME_BOT)$(NC) ready to use\n"

all: $(NAME)

bot: $(NAME_BOT)

# generate dependency files
# CXXFLAGS += -MMD

# leacks
# CXXFLAGS += -fsanitize=address

# for MacOs: cpp08
#	@$(CC) $(CXXFLAGS) $(OBJ) -o $(NAME) -lc++

# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./whatever

#--------------- CLEAN ----------------

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)[OK]\t$(RED)temporary object files deleted$(NC)"

clean_bot:
	@rm -rf $(NAME_BOT)
	@echo "$(GREEN)[OK]$(NC)\t$(NAME_BOT) $(RED)deleted$(NC)"

fclean: clean clean_bot
	@rm -f $(NAME)
	@echo "$(GREEN)[OK]$(NC)\t$(NAME) $(RED)deleted$(NC)"

re: fclean newLine all

#--------------- OTHER ----------------

newLine:
	@echo ""

.SILENT: $(OBJ) $(OBJ_BOT)

.PHONY: all re clean fclean newLine bot
