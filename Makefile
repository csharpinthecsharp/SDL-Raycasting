NAME	= a
CC		= clang
CFLAGS	= -g -Wall -Wextra -Werror

SRCS	= srcs/main.c \
		  srcs/parsing/p_av.c \
		  srcs/engine/init_sdl.c \
		  srcs/engine/free.c \
		  srcs/engine/key_handler.c \
		  srcs/engine/engine_loop.c \

OBJS	= $(SRCS:.c=.o)
LIBFT 	= libft/libft.a
CFLAGS 	= $(shell pkg-config --cflags sdl2)
LDFLAGS = $(shell pkg-config --libs sdl2)
LDFLAGS += -lm
all: $(NAME)

$(LIBFT):
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re