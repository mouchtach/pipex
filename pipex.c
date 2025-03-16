/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:06:41 by ymouchta          #+#    #+#             */
/*   Updated: 2025/03/16 19:54:51 by ymouchta         ###   ########.fr       */
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

void	child_p(t_pipe *val, int i)
{
	if (check_sq(val->argv[val->idex], 0) == 0)
		ft_error(NULL, NULL, 2);
	val->cmd = ft_split(val->argv[val->idex], ' ');
	val->path = ft_path(val->env);
	val->exec = check_acss(val->path, val->cmd[0]);
	ft_free_path(val);
	if (val->idex == i)
		first_cmd(val);
	else
		dup2(val->tmp_in, 0);
	if (val->idex == val->argc - 2)
		last_cmd(val);
	else
		dup2(val->fd[1], 1);
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

void	parent_p(t_pipe *val)
{
	close(val->fd[1]);
	if (val->tmp_in != 0)
		close(val->tmp_in);
	if (val->idex == val->argc - 2)
		close(val->tmp_in);
	else
		val->tmp_in = val->fd[0];
}

void	pipex(t_pipe *val)
{
	int	f;
	int	i;

	val->tmp_in = 0;
	i = val->idex;
	while (val->idex <= val->argc - 2)
	{
		if (val->idex != val->argc - 2)
			pipe(val->fd);
		f = fork();
		if (f == 0)
			child_p(val, i);
		if (f > 0)
			parent_p(val);
		val->idex++;
	}
	while (wait(NULL) > 0)
		;
	close(val->fd[0]);
	close(val->in);
	close(val->out);
}

int	main(int argc, char **argv, char **env)
{
	t_pipe	val;

	val.idex = 2;
	val.argc = argc;
	val.argv = argv;
	if (!env || !*env)
		ft_error(NULL, NULL, 3);
	if (argc < 5)
	{
		ft_putstr_fd("Error in argument\n", 2);
		exit(1);
	}
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		val.in = heredoc(argv[2]);
		val.idex = 3;
	}
	else
		val.in = open(argv[1], O_RDWR, 0777);
	val.out = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
	val.env = env;
	pipex(&val);
}
