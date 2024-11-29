NAME = get_next_line.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
BUFFER_SIZE = 42
SRCS = get_next_line.c get_next_line_utils.c
BONUS_SRCS = get_next_line_bonus.c get_next_line_utils_bonus.c
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
HEADER = get_next_line.h
BONUS_HEADER = get_next_line_bonus.h

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFFER_SIZE) -c $< -o $@

bonus: $(BONUS_OBJS)
	ar rcs $(NAME) $^

%.o: %.c $(BONUS_HEADER)
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFFER_SIZE) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus