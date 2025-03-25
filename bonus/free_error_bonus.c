/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:15:23 by ymouchta          #+#    #+#             */
/*   Updated: 2025/03/25 00:17:31 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free_command(t_pipe *val)
{
	int	i;

	i = 0;
	if (val->cmd)
	{
		while (val->cmd[i])
		{
			free(val->cmd[i]);
			i++;
		}
		val->cmd = NULL;
	}
}

void	ft_free_path(t_pipe *val)
{
	int	i;

	i = 0;
	if (val->path)
	{
		while (val->path[i])
		{
			free(val->path[i]);
			i++;
		}
		val->path = NULL;
	}
}

void	ft_error(t_pipe *val, char *str, int i)
{
	if (i == 0)
		ft_putstr_fd("command not found: ", 2);
	else if (i == 1)
		ft_putstr_fd("no such file or directory: ", 2);
	ft_putstr_fd(str, 2);
	write(2, "\n", 1);
	if (val)
	{
		free_all(val);
		if (val->exec)
			free(val->exec);
	}
	exit(1);
}

void	free_all(t_pipe *val)
{
	ft_free_command(val);
	ft_free_path(val);
	close(val->fd[1]);
	close(val->fd[0]);
	close(val->tmp_in);
	close(val->in);
	close(val->out);
}
