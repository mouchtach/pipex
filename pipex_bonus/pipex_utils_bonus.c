/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:20:49 by ymouchta          #+#    #+#             */
/*   Updated: 2025/03/20 02:00:36 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**ft_path(char **env)
{
	int		i;
	int		j;
	char	*str;

	str = "PATH";
	i = 0;
	while (env[i])
	{
		j = 0;
		if (env[i][j] == str[j])
		{
			while (str[j] == env[i][j] && str[j] && env[i][j])
				j++;
			if (str[j] == '\0')
				return (ft_split(env[i] + 5, ':'));
		}
		i++;
	}
	return (NULL);
}

char	*check_acss(char **path, char *cmd)
{
	int		i;
	char	*join;
	char	*tmp;

	i = 0;
	while (path[i])
	{
		join = ft_strjoin("/", cmd);
		tmp = ft_strdup(join);
		free(join);
		join = ft_strjoin(path[i], tmp);
		free(tmp);
		if (access(join, X_OK) == 0)
			return (join);
		i++;
	}
	free(join);
	return (NULL);
}

void	heredoc(t_pipe *val, char *dlm)
{
	char	*line;
	int fd;
	
	fd = open("/tmp/.here_doc", O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd == -1)
		ft_error(NULL, "herdoc error", 4);
	dlm = ft_strjoin(dlm, "\n");
	while (1)
	{
		write(1, "here_doc>", 9);
		line = get_next_line(STDIN_FILENO);
		if (ft_strcmp(line, dlm) == 0)
			break ;
		ft_putstr_fd(line,fd);
		free(line);
	}
	free(dlm);
	if (line)
		free(line);
	dup2(fd, 0);
	dup2(val->fd[1], 1);
	close(fd);
	close(val->fd[1]);
	close(val->fd[0]);
}

void	first_cmd(t_pipe *val)
{
	val->in = open(val->argv[1], O_RDWR, 0777);
	if(val->in == -1)
		ft_error(val, val->argv[val->index - 1], 1);
	dup2(val->in, 0);
	dup2(val->fd[1], 1);
	close(val->fd[0]);
	close(val->fd[1]);
	close(val->in);
}

void	last_cmd(t_pipe *val)
{
	if (val->heredoc == 1)
		val->out = open(val->argv[val->argc - 1], O_CREAT | O_APPEND | O_RDWR, 0777);
	else 
		val->out = open(val->argv[val->argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
	if(val->out == -1)
		ft_error(val, val->argv[val->index - 1], 1);
	dup2(val->out, 1);
	dup2(val->tmp_in, 0);
	close(val->fd[0]);
	close(val->fd[1]);
	close(val->out);
	close(val->tmp_in);
}
