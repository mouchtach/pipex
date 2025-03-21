/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_files_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:05:04 by ymouchta          #+#    #+#             */
/*   Updated: 2025/03/21 00:10:36 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	files_descriptor(t_pipe *val)
{
	if (val->index == 2)
		first_cmd(val);
	if (val->index == 3)
		last_cmd(val);
}

void	first_cmd(t_pipe *val)
{
	val->in = open(val->argv[1], O_RDWR, 0777);
	if (val->in == -1)
		ft_error(val, val->argv[1], 1);
	dup2(val->in, 0);
	dup2(val->fd[1], 1);
	close(val->fd[0]);
	close(val->fd[1]);
	close(val->in);
}

void	last_cmd(t_pipe *val)
{
	val->out = open(val->argv[val->argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (val->out == -1)
		ft_error(val, val->argv[val->argc - 1], 1);
	dup2(val->out, 1);
	dup2(val->fd[0], 0);
	close(val->fd[0]);
	close(val->fd[1]);
	close(val->out);
}
