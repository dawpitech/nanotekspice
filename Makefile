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

BDIR	=	.build

SRC	=	$(shell find src -name "*.cpp")

OBJ			= $(SRC:%.cpp=$(BDIR)/release/%.o)
DEBUG_OBJ	= $(SRC:%.cpp=$(BDIR)/debug/%.o)

NAME = nanotekspice

.DEFAULT_GOAL := all

.PHONY: all
all: $(NAME)

$(BDIR)/release/%.o: %.cpp
	@ mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CPPFLAGS)

$(NAME): $(OBJ)
	$(CC) $^ $(CPPFLAGS) -o $@

$(BDIR)/debug/%.o: %.cpp
	@ mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CPPFLAGS)

debug: CPPFLAGS += -g3 -O0 -DIS_DEBUG
debug: BDIR := .build/debug
debug: $(DEBUG_OBJ)
	$(CC) $^ $(CPPFLAGS) -o $@

.PHONY: clean
clean:
	@ rm -f $(OBJ)
	@ rm -f $(DEPS)
	@ rm -rf .build

.PHONY: fclean
fclean: clean
	@ rm -f $(NAME)

.NOTPARALLEL: re
.PHONY: re
re: fclean all

-include $(OBJ:.o=.d)
-include $(DEBUG_OBJ:.o=.d)
