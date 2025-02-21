##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile
##

CC	:=	g++

CXXFLAGS	=	-std=c++20
CXXFLAGS	+=	-W
CXXFLAGS	+=	-Wall
CXXFLAGS	+=	-Wextra
CXXFLAGS	+=	-Wundef
CXXFLAGS	+=	-Wshadow
CXXFLAGS	+=	-Wunreachable-code
CXXFLAGS	+=	-pedantic
CXXFLAGS	+=	-iquote .
CXXFLAGS	+=	-MMD -MP

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
	$(CC) -o $@ -c $< $(CXXFLAGS)

$(NAME): $(OBJ)
	$(CC) $^ $(CXXFLAGS) -o $@

$(BDIR)/debug/%.o: %.cpp
	@ mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(CXXFLAGS)

debug: CXXFLAGS += -g3 -O1 -DIS_DEBUG
debug: BDIR := .build/debug
debug: $(DEBUG_OBJ)
	$(CC) $^ $(CXXFLAGS) -o $@

.PHONY: clean
clean:
	@ rm -f $(OBJ)
	@ rm -f $(DEPS)
	@ rm -rf .build

.PHONY: fclean
fclean: clean
	@ rm -f $(NAME)
	@ rm -f debug

.NOTPARALLEL: re
.PHONY: re
re: fclean all

-include $(OBJ:.o=.d)
-include $(DEBUG_OBJ:.o=.d)
