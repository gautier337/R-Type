##
## EPITECH PROJECT, 2023
## R-TYPE
## File description:
## Makefile
##

SRC			=	src/Client.cpp	\
				src/Game.cpp	\
				src/Main.cpp

OBJ = $(SRC:.cpp=.o)
OBJ += $(COMMON_SRC:.cpp=.o)

NAME		=	r-type_client

CXXFLAGS	+=	-std=c++17

CPPFLAGS	=	-I./include -W -Wall -Wextra -Werror -pedantic

LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -pthread

all:			$(NAME)

$(NAME):		$(OBJ)
				g++ -o $(NAME) $(SRC) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS)

clean:
				@find . -type f | xargs touch
				@rm -f $(OBJ)
				@rm -f *.o
				@rm -f src/main.o
				@rm -f *~
				@rm -f vgcore*
				@rm -f #*
				@rm -f *.gcda
				@rm -f *.identifier
				@rm -f *.gcno

debug: CPPFLAGS += -g -ggdb3
ifeq ($(UNAME), Darwin)
	debug: CPPFLAGS += -fsanitize=address
endif
debug: 			re

fclean: 		clean
				rm -f $(NAME)
				@rm -f covr/*.html
				@rm -f covr/*.css
				@rm -rf covr/
				@rm -f *.gcno

re:				fclean all

.PHONY:			all clean tests_run all re