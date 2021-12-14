# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tbruinem <tbruinem@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/06/21 23:18:21 by tbruinem      #+#    #+#                  #
#    Updated: 2021/06/21 23:31:43 by tbruinem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =	libtrie.a
SRCDIR = src
OBJDIR = obj
INCDIR = incl

CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I $(INCDIR) 

ifeq ($(DEBUG),1)
	CFLAGS += -g -fsanitize=address
endif

OBJ =	trie.o
OBJ :=	$(OBJ:%=$(OBJDIR)/%)

all: $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $@

$(NAME): $(OBJ)
	$(AR) -rcs $@ $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
