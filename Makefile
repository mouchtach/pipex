NAME = pipex
BNAME = bonus/.pb

SOURCES =  Mandatory/dup_files.c Mandatory/ft_split.c Mandatory/libft.c Mandatory/libft2.c \
		Mandatory/pipex.c Mandatory/free_error.c Mandatory/pipex_utils.c Mandatory/ft_split_utils.c

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
	$(CC) $(CFLAGS) $(OBJECTS) -o $@
	rm -rf $(BOBJECTS)
	rm -rf $(BNAME)

$(BNAME) : $(BOBJECTS) 
	$(CC) $(CFLAGS) $(BOBJECTS) -o $(NAME)
	rm -rf $(OBJECTS)
	touch $(BNAME)

	
Mandatory/%.o: Mandatory/%.c Mandatory/pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus/%.o: bonus/%.c bonus/pipex_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@	

clean:
	rm -rf $(OBJECTS) $(BOBJECTS)

fclean: clean
	rm -rf $(BNAME) $(NAME) 

re: fclean all

PHONY: all clean fclean re bonus
