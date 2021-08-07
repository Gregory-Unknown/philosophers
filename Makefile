NAME		= philo

INC			= philos.h

SRCS		= main.c philos.c ft_utils.c

OBJ			= $(SRCS:.c=.o)

CC			= gcc -g -Wall -Wextra -Werror

RM			= rm -f

$(NAME):	$(OBJ) $(INC)
			$(CC) -o $(NAME) $(OBJ)

all:		$(NAME)

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) ${NAME}

re:			fclean all
