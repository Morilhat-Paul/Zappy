##
## EPITECH PROJECT, 2024
## B-YEP-400-LYN-4-1-zappy-paul.morilhat
## File description:
## Makefile
##

AI = ./ai

GRAPIC = ./gui

SERVER = ./server

MAKE = make -s -C
MAKE_CLEAN = make -s clean -C
MAKE_FCLEAN = make -s fclean -C
MAKE_RE = make -s re -C

all: zappy_ai zappy_gui zappy_server

zappy_ai:
	@$(MAKE) $(AI)

zappy_gui:
	@$(MAKE) $(GRAPIC)

zappy_server:
	@$(MAKE) $(SERVER)

ai_clean:
	@$(MAKE_CLEAN) $(AI)

gui_clean:
	@$(MAKE_CLEAN) $(GRAPIC)

server_clean:
	@$(MAKE_CLEAN) $(SERVER)

clean: ai_clean server_clean gui_clean

ai_fclean:
	@$(MAKE_FCLEAN) $(AI)

gui_fclean:
	@$(MAKE_FCLEAN) $(GRAPIC)

server_fclean:
	@$(MAKE_FCLEAN) $(SERVER)

fclean: ai_fclean server_fclean gui_fclean

ai_re:
	@$(MAKE_RE) $(AI)

gui_re:
	@$(MAKE_RE) $(GRAPIC)

server_re:
	@$(MAKE_RE) $(SERVER)

re: ai_re server_re gui_re

.PHONY: re server_re gui_re ai_re \
	fclean server_fclean gui_fclean ai_fclean \
	clean server_clean gui_clean ai_clean \
	all zappy_server zappy_gui zappy_ai
