SOURCES = ft_split.c libft.c pipex.c heredoc.c get_next_line.c free_error.c pipex_utils.c
OBJECTS = $(SOURCES:.c=.o)
AR = ar rcs
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(OBJECTS)
	$(CC)  $(OBJECTS) -o pipex

%.o: %.c pipex.h
	$(CC)  $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(BOBJECTS)

fclean: clean
	rm -rf pipex

re: fclean all