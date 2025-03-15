/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:22:10 by ymouchta          #+#    #+#             */
/*   Updated: 2025/03/15 19:11:49 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct t_pipe
{
	int		argc;
	int		in;
	int		out;
	int		fd[2];
	char	**cmd;
	char	**argv;
	char	**env;
	char	**path;
	char	*exec;
	int		idex;
	int		tmp_in;

}			t_pipe;

// libft2
char		*ft_strchr(const char *s, int c);
void		ft_putstr_fd(char *s, int fd);
int			ft_strcmp(const char *s1, const char *s2);

// libft
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);

// heredoc
int			heredoc(char *argv);

// get_next_line;
char		*get_next_line(int fd);

// free_error
void		ft_error(t_pipe *val, char *str, int i);
void		ft_free_path(t_pipe *val);
void		ft_free_command(t_pipe *val);
void		free_all(t_pipe *val);

// pipex_utils
char		**ft_path(char **env);
char		*check_acss(char **path, char *cmd);
void		child_p(t_pipe *val, int i);
void		parent_p(t_pipe *val);
void		pipex(t_pipe *val);

#endif 
