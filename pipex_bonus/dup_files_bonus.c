/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_files_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:05:04 by ymouchta          #+#    #+#             */
/*   Updated: 2025/03/20 17:11:46 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	files_descriptor(t_pipe *val)
{
	int	fd;

	if (val->heredoc == 1 && val->index == 3)
	{
		fd = heredoc(val->argv[2]);
		dup2(fd, 0);
		dup2(val->fd[1], 1);
		close(fd);
		close(val->fd[1]);
		close(val->fd[0]);
	}
	else if (val->heredoc == 0 && val->index == 2)
		first_cmd(val);
	else if (val->index == val->argc - 2)
		last_cmd(val);
	else
	{
		dup2(val->tmp_in, 0);
		dup2(val->fd[1], 1);
		close(val->tmp_in);
		close(val->fd[1]);
		close(val->fd[0]);
	}
}

int	heredoc(char *dlm)
{
	char	*line;
	int		fd;

	fd = open("/tmp/here_doc", O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd == -1)
		ft_error(NULL, "herdoc error", 4);
	dlm = ft_strjoin(dlm, "\n");
	while (1)
	{
		write(1, "here_doc>", 9);
		line = get_next_line(STDIN_FILENO);
		if (ft_strcmp(line, dlm) == 0)
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(dlm);
	if (line)
		free(line);
	close(fd);
	fd = open("/tmp/here_doc", O_RDONLY, 0777);
	return (fd);
}

void	first_cmd(t_pipe *val)
{
	val->in = open(val->argv[1], O_RDWR, 0777);
	if (val->in == -1)
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
		val->out = open(val->argv[val->argc - 1], O_CREAT | O_APPEND | O_RDWR,
				0777);
	else
		val->out = open(val->argv[val->argc - 1], O_CREAT | O_TRUNC | O_RDWR,
				0777);
	if (val->out == -1)
		ft_error(val, val->argv[val->index - 1], 1);
	dup2(val->out, 1);
	dup2(val->tmp_in, 0);
	close(val->fd[0]);
	close(val->fd[1]);
	close(val->out);
	close(val->tmp_in);
}
