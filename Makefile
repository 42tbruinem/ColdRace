# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tbruinem <tbruinem@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/12/14 14:25:31 by tbruinem      #+#    #+#                  #
#    Updated: 2021/12/14 15:10:56 by tbruinem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = coldrace
SRC =	main.c
HEADER	=	./incl/coldrace.h \
			./lib/libtrie/incl/libtrie.h \
			./lib/gnl/get_next_line.h
LIBRARY	=	./lib/libtrie/libtrie.a \
			./lib/gnl/libgnl.a
OBJ_DIR = ./obj
SRC_DIR = ./src
CC = gcc
CFLAGS = -Wall -Wextra -Werror

ifeq ($(DEBUG),1)
	CFLAGS += -g -fsanitize=address
endif

INCL	:=	$(addprefix -I ,$(dir $(HEADER)))

OBJ 	:=	$(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

./lib/gnl/libgnl.a:
	@$(MAKE) -sC $(dir $@) DEBUG=$(DEBUG)

./lib/libtrie/libtrie.a:
	@$(MAKE) -sC $(dir $@) DEBUG=$(DEBUG)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $(notdir $@)"
	@$(CC) $(CFLAGS) -c $^ $(INCL) -o $@

$(NAME): $(OBJ) $(LIBRARY)
	$(CC) $(CFLAGS) $(OBJ) $(INCL) -L ./lib/gnl -lgnl -L ./lib/libtrie -ltrie -o $@ 

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all