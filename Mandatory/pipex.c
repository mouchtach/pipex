/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:06:41 by ymouchta          #+#    #+#             */
/*   Updated: 2025/03/22 19:50:56 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_sq(char *arg, int i)
{
	while (arg[i])
	{
		if (arg[i] == '\'')
		{
			i++;
			while (arg[i] != '\'' && arg[i])
				i++;
			if (arg[i] == '\'')
				return (1);
			else
				return (0);
		}
		i++;
	}
	return (1);
}

void	wait_and_error(int *check)
{
	int	status;

	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) > 0)
				*check = 1;
		}
	}
}

void	pipex(t_pipe *val)
{
	int	f;
	int	check;

	check = 0;
	if (pipe(val->fd) == -1)
		ft_error(NULL, "pipe faild", 2);
	while (val->index <= val->argc - 2)
	{
		if (val->index == 3)
			close(val->fd[1]);
		f = fork();
		if (f < 0)
			ft_error(NULL, "fork faild", 2);
		if (f == 0)
			child_p(val);
		val->index++;
	}
	wait_and_error(&check);
	close(val->fd[0]);
	if (check == 1)
		exit(1);
}

int	main(int argc, char **argv, char **env)
{
	t_pipe	val;

	if (!env || !*env)
		ft_error(NULL, "envirement variable doesn\'t exist", 2);
	if (argc == 5)
	{
		val.index = 2;
		val.argc = argc;
		val.argv = argv;
		val.env = env;
		pipex(&val);
	}
	else
		ft_error(NULL, "Error in argument", 2);
}
