##
## EPITECH PROJECT, 2024
## B-YEP-400-LYN-4-1-zappy-paul.morilhat
## File description:
## Makefile
##

SRC = src/main.py
NAME = ../zappy_ai

GREEN=\033[0;32m
RED=\033[0;31m
NC=\033[0m

all: $(NAME)
	@echo -e "$(GREEN)//---- Compilation completed. ----//$(NC)"

$(NAME): $(SRC)
	@cp $< $@ && chmod +x $@
	@echo -e	\
	"$(GREEN)//---- The $(NAME) executable file has been created. ----//$(NC)"

clean:
	@rm -f $(NAME)
	@rm -rf */**/__pycache__
	@echo -e "$(RED)//---- Cleaning completed. ----//$(NC)"

fclean: clean

re: fclean all

.PHONY: clean fclean re
