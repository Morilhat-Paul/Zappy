##
## EPITECH PROJECT, 2024
## server
## File description:
## Makefile
##

# This is a minimal set of ANSI/VT100 color codes
END		=	"\e[0m"
BOLD	=	"\e[1m"
ITALIC	=	"\e[3m"
DIM		=	"\e[2m"
RDIM	=	"\e[22m"

# Colors
GREEN	=	"\e[32m"
PURPLE	=	"\e[35m"
BLUE	=	"\e[36m"
LYELLOW	=	"\e[93m"



## 		OPTIONS 	##

TARGET				= 	../zappy_server
SOURCE_DIR			=	sources
OBJECT_DIR			=	objects
HEADER_DIR			=	includes
TEST_DIR			=	tests
MAKE				=	make -s -C
MKDIR				=	mkdir -p
RM					=	rm -rf
PRINT				=	echo

vpath %.c $(SOURCE_DIR)



## PRINTING ##

BUILD_DONE		= 	\
${BOLD}${GREEN}"=== Building\t\t\t\t"${ITALIC}"DONE !"			${END}

BUILD_PROGRESS	=	\
${BOLD}${LYELLOW}"=== Building\t\t\t\t"${ITALIC}"IN PROGRESS"	${END}

CLEAN_BIN		= 	\
${BOLD}${GREEN}"=== Cleaning binary\t\t\t\t"${ITALIC}"DONE"		${END}

CLEAN_OBJ		= 	\
${BOLD}${GREEN}"=== Cleaning object\t\t\t\t"${ITALIC}"DONE !"	${END}

COMPILING		= 	\
${BOLD}${PURPLE}"=== Compiling $<"								${END}



## COMPILER OPTIONS ##

CC			=	gcc
AR			=	ar rc
CFLAGS		+=	-W -Wall -Wextra	\
				-I ${HEADER_DIR}	\
				-MD	\
				-g3
LDFLAGS		+=


## 	SOURCES FILES 	##

SRC		=	$(wildcard ${SOURCE_DIR}/*.c)
SRC		+=	$(wildcard ${SOURCE_DIR}/function/*.c)
SRC		+=	$(wildcard ${SOURCE_DIR}/gui_function/*.c)


## 	OBJECT FILES 	##

OBJ		=	${SRC:%.c=${OBJECT_DIR}/%.o}

${OBJECT_DIR}/%.o : %.c
	@$(MKDIR) $(dir $@)
	@$(CC) -c $< -o $@ ${CFLAGS}
	@$(PRINT) ${COMPILING}



##		RECIPES		##

.PHONY: all re clean fclean lib

all: lib ${TARGET}

clean:
	@$(RM) ${OBJECT_DIR}
	@$(PRINT) ${CLEAN_OBJ}

fclean: clean
	@$(RM) ${TARGET}
	@$(PRINT) ${CLEAN_BIN}

re: fclean all

-include $(OBJ:%.o=%.d)

tests_run:
	@$(MAKE) ${TEST_DIR}

tests_re:
	@$(MAKE) ${TEST_DIR} re

tests_display:
	@$(MAKE) ${TEST_DIR} display



##	FILE GENERATOR	##

$(TARGET): $(OBJ)
	@$(PRINT) ${BUILD_PROGRESS}
	@$(CC) -o $@ ${CFLAGS} $^ ${LDFLAGS}
	@$(PRINT) ${BUILD_DONE}
