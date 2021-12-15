
# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tbruinem <tbruinem@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/12/14 14:25:31 by tbruinem      #+#    #+#                  #
#    Updated: 2021/12/14 15:49:55 by tbruinem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = coldrace
SRC =	strlen.c \
		hashmap.c \
		strcmp.c \
		memcmp.c \
		storage.c \
		search.c \
		min.c

ifdef WITHBONUS
SRC +=	main_bonus.c
else
SRC +=	main.c
endif

HEADER	=	./incl/coldrace.h \
			./incl/hashmap.h \
			./incl/util.h \
			./lib/gnl/incl/ft_get_next_line.h
LIBRARY	=	./lib/gnl/libgnl.a
OBJ_DIR = ./obj
SRC_DIR = ./src
CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3

ifeq ($(DEBUG),1)
	CFLAGS += -g -fsanitize=address
endif

INCL	:=	$(addprefix -I ,$(dir $(HEADER)))

OBJ 	:=	$(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

bonus:
	$(MAKE) WITHBONUS=1 all

./lib/gnl/libgnl.a:
	@$(MAKE) -sC $(dir $@) DEBUG=$(DEBUG)

./lib/libtrie/libtrie.a:
	@$(MAKE) -sC $(dir $@) DEBUG=$(DEBUG)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@echo "Compiling $(notdir $@)"
	@$(CC) $(CFLAGS) -c $^ $(INCL) -o $@

$(NAME): $(OBJ) $(LIBRARY)
	$(CC) $(CFLAGS) $(OBJ) $(INCL) -L ./lib/gnl -lgnl -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
