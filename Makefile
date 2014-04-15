##
## Makefile for MAKEFILE in /home/marcha_j//test/c/malloc/proj
## 
## Made by hugo marchadier
## Login   <marcha_j@epitech.net>
## 
## Started on  Wed Feb  1 18:08:19 2012 hugo marchadier
## Last update Fri May  4 18:11:52 2012 hugo marchadier
##

NAME=	strace

SRC=	main.c \
	strace.c \
	print.c \
	get_str.c \
	xfct.c \

CC=	gcc

CFLAGS+= -W -Wall -Wextra -ansi -pedantic -D_XOPEN_SOURCE=700

OBJ=    $(SRC:.c=.o)

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re