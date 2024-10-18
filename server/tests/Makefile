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

TARGET_NAME			=	unit_tests
PROJECT_NAME		=	server
SOURCE_DIR			=	../sources
HEADER_DIR			=	../includes
OBJECT_DIR			=	objects
SRC_UNIT_DIR		=	src
CRITERION			=	--coverage -lcriterion
GCOVR				=	gcovr
GCOVR				+=	--exclude ${SRC_UNIT_DIR}
GCOVR				+=	--root ..
MKDIR				=	mkdir -p
RM					=	rm -rf
PRINT				=	echo



## PRINTING ##

BUILD_DONE 		= 	\
${BOLD}${GREEN}"=== Building tests\t\t\t\t"${ITALIC}"DONE !"		${END}

BUILD_PROGRESS	= 	\
${BOLD}${LYELLOW}"=== Building tests\t\t\t\t"${ITALIC}"IN PROGRESS"	${END}

CLEAN_TESTS 	=	\
${BOLD}${GREEN}"=== Cleaning testing files\t\t\t"${ITALIC}"DONE !"	${END}

CLEAN_TESTS_BIN =	\
${BOLD}${GREEN}"=== Cleaning binary test\t\t\t"${ITALIC}"DONE !"	${END}

COMPILING 		=	\
${BOLD}${PURPLE}"=== Compiling $<" 									${END}



## COMPILER OPTIONS ##

CC			=	gcc
CFLAGS		+=	-W -Wall -Wextra -Werror	\
				-I${HEADER_DIR}



## 	SOURCES FILES 	##

SRC 		:= $(filter-out ${SOURCE_DIR}/main.c, $(wildcard ${SOURCE_DIR}/*.c))
SRC			+= $(wildcard ${SOURCE_DIR}/function/*.c)

UNIT_TESTS	:= $(wildcard ${SRC_UNIT_DIR}/command/*.c)
UNIT_TESTS	+= $(wildcard ${SRC_UNIT_DIR}/message/*.c)



## 	OBJECT FILES 	##

OBJ		=	${SRC:${SOURCE_DIR}/%.c=${OBJECT_DIR}/%.o}

${OBJECT_DIR}/%.o : ${SOURCE_DIR}/%.c
	@$(MKDIR) $(dir $@)
	@$(CC) -c $< -o $@ ${CFLAGS} ${LFLAGS} ${CRITERION}
	@$(PRINT) ${COMPILING}



##		RECIPES		##

.PHONY: all re clean fclean

all: $(TARGET_NAME)
	@./$<

clean:
	@$(RM) *.gc*
	@$(RM) *.gcov
	@$(RM) $(OBJECT_DIR)
	@$(PRINT) ${CLEAN_TESTS}

fclean: clean
	@$(RM) ${COV_REPORT}
	@$(RM) ${TARGET_NAME}
	@$(PRINT) ${CLEAN_TESTS_BIN}

re: fclean all

display:
	@$(GCOVR) --branches --print-summary
	@$(GCOVR)



##	FILE GENERATOR	##

$(TARGET_NAME): $(OBJ)
	@$(CC) -o $@ ${CFLAGS} $^ ${UNIT_TESTS} ${CRITERION}
	@$(PRINT) $(BUILD_DONE)
