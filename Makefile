NAME = pipex
SOURCES = ft_split.c libft.c libft2.c pipex.c free_error.c pipex_utils.c ft_split_utils.c
OBJECTS = $(SOURCES:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $@

bonus:
	@make -C bonus
	
%.o: %.c pipex.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJECTS)
	@make -C bonus clean

fclean: clean
	@rm -rf pipex
	@make -C bonus fclean

re: fclean all

.PHONY:  bonus