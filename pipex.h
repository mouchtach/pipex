/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:22:10 by ymouchta          #+#    #+#             */
/*   Updated: 2025/03/11 23:03:13 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct t_pipe
{
    int argc;
    int in;
    int out;
    int fd[2];
    char **cmd;
    char **argv;
    char **env;
    int idex;
    int tmp_in;
    
}t_pipe ;


// libft
size_t	ft_strlen(const char *s);  
char	*ft_strchr(const char *s, int c);
int     ft_strcmp(const char *s1, const char *s2);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);

//heredoc
int     heredoc(char *argv);


//get_next_line;
char	*get_next_line(int fd);


#endif // 
