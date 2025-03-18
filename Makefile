NAME = pipex
SOURCES = ft_split.c libft.c libft2.c pipex.c  \
		free_error.c pipex_utils.c ft_split_utils.c

OBJECTS = $(SOURCES:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME) 

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $@

bonus:
	@make -C pipex_bonus
	
%.o: %.c pipex_bonus.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C pipex_bonus clean
	@rm -rf $(OBJECTS)

fclean: clean
	@make -C pipex_bonus fclean
	@rm -rf pipex

re: fclean all
