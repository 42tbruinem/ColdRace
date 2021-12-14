# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jvan-sni <jvan-sni@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/28 16:59:45 by jvan-sni      #+#    #+#                  #
#    Updated: 2021/12/14 15:00:17 by tbruinem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libgnl.a
CFLAGS = -Wall
BUFFER_SIZE=5
VARS = -D BUFFER_SIZE=${BUFFER_SIZE}
CC = gcc

FILES = main.c get_next_line.c get_next_line_utils.c
OBJ = $(FILES:%.c=%.o)
ifdef BONUS
FILES = main_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c
endif
HEADERS = get_next_line.h

all: $(NAME)

%.o : %.c
	@mkdir -p $(@D)
	@echo "Compiling $(notdir $@)"
	@$(CC) $(CFLAGS) -c $^ $(INCL) -o $@

$(NAME): $(OBJ)
	$(AR) -rcs $@ $^

fclean:
	rm -f $(NAME)

re: fclean all

# GNL: fclean
# 	gcc -Wall -Wextra -Werror $(FILES) -D BUFFER_SIZE=$(BUFFER_SIZE)

# GNL_INF: fclean
# 	gcc -Wall -Wextra -Werror $(FILES) -D BUFFER_SIZE=$(BUFFER_SIZE) -D INF

test:
	sh run_test.sh

fulltest: norm test

norm:
	norminette $(FILES) $(HEADERS)
