# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/26 16:49:31 by yadereve          #+#    #+#              #
#    Updated: 2025/03/25 11:18:54 by gneto-co         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv
CC = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SRC_DIR = sources
OBJ_DIR = objects

SRC_FILE = main.cpp Server.cpp Client.cpp
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILE))
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.cpp=.o)))

NC = \033[0m
RED = \033[31m
ORANGE = \033[33m
GREEN = \033[92m

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) -c $(CXXFLAGS) -o $@ $<
	@echo "[OK]\t$(ORANGE)"$@"$(NC)"

$(NAME): $(OBJ)
	@$(CC) $(CXXFLAGS) $(OBJ) -o $(NAME)
	@echo "[OK]\t$(GREEN)$(NAME)$(NC) ready to use"
	@echo "------------------------------"

all: $(NAME)

# generate dependency files
# CXXFLAGS += -MMD

# leacks
# CXXFLAGS += -fsanitize=address

# for MacOs: cpp08
#	@$(CC) $(CXXFLAGS) $(OBJ) -o $(NAME) -lc++

# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./whatever
clean:
	@rm -rf $(OBJ_DIR)
	@echo "[OK]\t$(RED)temporary object files deleted$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "[OK]\t$(NAME) $(RED)deleted$(NC)"

newLine:
	@echo ""

re: fclean newLine all

.SILENT: $(OBJ)

.PHONY: all re clean fclean newLine
