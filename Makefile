##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile
##

CC	:=	g++

CPPFLAGS	=	-std=c++20
CPPFLAGS	+=	-W
CPPFLAGS	+=	-Wall
CPPFLAGS	+=	-Wextra
CPPFLAGS	+=	-Wundef
CPPFLAGS	+=	-Wshadow
CPPFLAGS	+=	-Wunreachable-code
CPPFLAGS	+=	-pedantic
CPPFLAGS	+=	-iquote .
CPPFLAGS	+=	-MMD -MP

BDIR	=	.build/release

SRC	=	$(shell find src -name "*.cpp")

OBJ = $(SRC:%.cpp=$(BDIR)/%.o)
DEPS	=	$(OBJ:.o=.d)

NAME = nanotekspice

.PHONY: all
all: $(NAME)

$(BDIR)/%.o: %.cpp
	@ mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CPPFLAGS)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CPPFLAGS) -o $(NAME)

debug: CPPFLAGS += -g3 -O0 -DIS_DEBUG
debug: re

.PHONY: clean
clean:
	@ rm -f $(OBJ)
	@ rm -rf .build

.PHONY: fclean
fclean: clean
	@ rm -f $(NAME)

.NOTPARALLEL: re
.PHONY: re
re: fclean all

-include $(DEPS)
