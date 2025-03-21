NAME = pipex
BNAME = pipex_bonus
SOURCES = ft_split.c libft.c libft2.c pipex.c  \
		free_error.c pipex_utils.c ft_split_utils.c

BSOURCES = bonus/dup_files_bonus.c bonus/free_error_bonus.c bonus/ft_split_bonus.c \
		bonus/ft_split_utils_bonus.c bonus/get_next_line_bonus.c bonus/libft_bonus.c \
		bonus/libft2_bonus.c bonus/pipex_bonus.c bonus/pipex_utils_bonus.c

OBJECTS = $(SOURCES:.c=.o)
BOBJECTS = $(BSOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME) 

bonus: $(BNAME) 

$(NAME): $(OBJECTS)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $@

$(BNAME): $(BOBJECTS)
	@$(CC) $(CFLAGS) $(BOBJECTS) -o $@
	
%.o: %.c pipex.h
	@$(CC) $(CFLAGS) -c $< -o $@

bonus/%.o: bonus/%.c bonus/pipex_bonus.h
	@$(CC) $(CFLAGS) -c $< -o $@	

clean:
	@rm  $(OBJECTS) $(BOBJECTS)

fclean: clean
	@rm -rf pipex

re: fclean all
