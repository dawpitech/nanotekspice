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

T_CXXFLAGS	:= $(CXXFLAGS)
T_CXXFLAGS	+=	-g3 -lcriterion --coverage

BDIR	=	.build

SRC	=	$(shell find src -name "*.cpp" -not -path "*/main/*")

T_SRC	:=	$(SRC)
T_SRC	+=	$(shell find tests -name "*.cpp")

SRC	+=	src/main/main.cpp

OBJ			= $(SRC:%.cpp=$(BDIR)/release/%.o)
DEBUG_OBJ	= $(SRC:%.cpp=$(BDIR)/debug/%.o)
T_OBJ		= $(T_SRC:%.cpp=$(BDIR)/test/%.o)

NAME = nanotekspice
T_NAME	=	unit_tests

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

$(BDIR)/test/%.o: %.cpp
	@ mkdir -p $(dir $@)
	$(CC) -o $@ -c $< $(T_CXXFLAGS)

$(T_NAME): $(T_OBJ)
	$(CC) $^ $(T_CXXFLAGS) -o $@

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
-include $(T_OBJ:.o=.d)
