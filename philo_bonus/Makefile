NAME    = philo_bonus
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g
SRCS    = init_bonus.c main_bonus.c routine_bonus.c \
			supervise_bonus.c utils_bonus.c

OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -pthread -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re