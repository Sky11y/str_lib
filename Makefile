NAME		= libstr_lib.a

SRCDIR		= src/
INCDIR		= inc/
BUILDDIR	= build/

CC			= gcc
CFLAGS		= -Wall -O2 -Wextra -Werror -pedantic -I$(INCDIR)

SRC			= $(wildcard $(SRCDIR)*.c)
OBJ			= $(SRC:$(SRCDIR)%.c=$(BUILDDIR)%.o)

all: $(NAME)

$(NAME): $(OBJ)
		ar rcs $@ $^

$(BUILDDIR)%.o: $(SRCDIR)%.c | $(BUILDDIR)
		$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR):
		mkdir -p $@

clean:
		rm -rf $(BUILDDIR)

fclean:	clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
