# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tbruinem <tbruinem@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/12/14 14:25:31 by tbruinem      #+#    #+#                  #
#    Updated: 2021/12/14 14:35:06 by tbruinem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = coldrace
SRC =	main.c
HEADER	=	./incl/coldrace.h \
			./lib/libtrie/incl/libtrie.h
LIBRARY	=	./lib/libtrie/libtrie.a
OBJ_DIR = ./obj
SRC_DIR = ./src
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCL	:=	$(addprefix -I ,$(dir $(HEADER)))

OBJ 	:=	$(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

./lib/libtrie/libtrie.a:
	@$(MAKE) -sC $(dir $@) DEBUG=$(DEBUG)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $(notdir $@)"
	@$(CC) $(CFLAGS) -c $^ $(INCL) -o $@

$(NAME): $(OBJ) $(LIBRARY)
	$(CC) $(CFLAGS) $(OBJECTS) $(INCL) -L ./lib/libtrie -ltrie -o $@ 

clean:
	rm -rf $(OBJ)

fclean:
	rm -rf $(NAME)

re: fclean all