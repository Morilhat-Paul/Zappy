##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Makefile
##

TARGET = ../zappy_gui

GREEN=\033[0;32m
RED=\033[0;31m
NC=\033[0m

CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

SRCDIR = src
OBJ = obj
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJ)/%.o,$(SOURCES))

INCLUDES = -I/usr/include -I/usr/local/include -I/usr/include/glm -I include/

LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lGL -lGLU -lsfml-network

all: $(TARGET)
	@echo -e "$(GREEN)//---- Compilation completed. ----//$(NC)"

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(OBJ)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<
	@echo -e "$(GREEN)//---- The $(NAME) executable file has been created. ----//$(NC)"

clean:
	rm -rf $(OBJ) $(TARGET)
	@echo -e "$(RED)//---- Cleaning completed. ----//$(NC)"

fclean: clean
	rm -rf $(OBJ) $(TARGET)

re: fclean all

.PHONY: all clean fclean re
