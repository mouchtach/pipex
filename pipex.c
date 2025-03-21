/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:06:41 by ymouchta          #+#    #+#             */
/*   Updated: 2025/03/21 00:31:09 by ymouchta         ###   ########.fr       */
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

void	child_p(t_pipe *val)
{
	if (check_sq(val->argv[val->index], 0) == 0)
		ft_error(NULL, NULL, 2);
	val->cmd = ft_split(val->argv[val->index], ' ');
	val->path = ft_path(val->env);
	val->exec = check_acss(val->path, val->cmd[0]);
	ft_free_path(val);
	if (val->index == 2)
		first_cmd(val);
	if (val->index == 3)
		last_cmd(val);
	close(val->fd[0]);
	close(val->fd[1]);
	if (val->exec == NULL)
		ft_error(val, val->cmd[0], 0);
	if (execve(val->exec, val->cmd, NULL) == -1)
	{
		free_all(val);
		if (val->exec)
			free(val->exec);
	}
}

void	pipex(t_pipe *val)
{
	int	f;

	pipe(val->fd);
	while (val->index <= val->argc - 2)
	{
		f = fork();
		if (f == 0)
			child_p(val);
		if (f > 0)
		{
			if (val->index == 3)
				close(val->fd[1]);
		}
		val->index++;
	}
	while (wait(NULL) > 0)
		;
	close(val->in);
	close(val->fd[0]);
	close(val->out);
}

int	main(int argc, char **argv, char **env)
{
	t_pipe	val;

	if (!env || !*env)
		ft_error(NULL, NULL, 3);
	if (argc == 5)
	{
		val.index = 2;
		val.argc = argc;
		val.argv = argv;
		val.in = open(argv[1], O_RDWR, 0777);
		val.out = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
		val.env = env;
		pipex(&val);
	}
	else
	{
		ft_putstr_fd("Error in argument\n", 2);
		exit(1);
	}
}
