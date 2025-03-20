NAME = pipex
SOURCES = ft_split_bonus.c libft_bonus.c libft2_bonus.c pipex_bonus.c  get_next_line_bonus.c  \
		free_error_bonus.c pipex_utils_bonus.c ft_split_utils_bonus.c dup_files_bonus.c

OBJECTS = $(SOURCES:.c=.o)
CC = cc
# CFLAGS = -Wall -Wextra -Werror

all: $(NAME) 

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $@
	
%.o: %.c pipex_bonus.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJECTS)

fclean: clean
	@rm -rf pipex

re: fclean all