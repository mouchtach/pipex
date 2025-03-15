SOURCES = ft_split.c libft.c libft2.c pipex.c heredoc.c get_next_line.c free_error.c pipex_utils.c
OBJECTS = $(SOURCES:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: pipex

pipex: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o pipex
	
%.o: %.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf pipex

re: fclean all