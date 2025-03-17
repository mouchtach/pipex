/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:47:52 by ymouchta          #+#    #+#             */
/*   Updated: 2025/03/17 17:59:11 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct t_pipe
{
    int fd[2];
    int index;
    int in;
    int out;
    int argc;
    char **argv;
    char **env;
    char **cmd;
    char **path;
    char *exec;

}t_pipe;

//split
char	**ft_split(char const *s, char c);
char	*single_quote(const char *str, size_t *i);

//libft
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);

//libft2
int     ft_strcmp(const char *s1, const char *s2);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);

//error
void	ft_free_command(t_pipe *val);
void	ft_free_path(t_pipe *val);
void	ft_error(t_pipe *val, char *str, int i);
void	free_all(t_pipe *val);


// util pipex
void	last_cmd(t_pipe *val);
void	first_cmd(t_pipe *val);
char	*check_acss(char **path, char *cmd);
char	**ft_path(char **env);


#endif