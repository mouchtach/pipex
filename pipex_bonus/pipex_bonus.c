/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:06:41 by ymouchta          #+#    #+#             */
/*   Updated: 2025/03/20 02:00:22 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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



void	files_descriptor(t_pipe *val)
{
	if (val->heredoc == 1 && val->index == 3)
		heredoc(val, val->argv[2]);
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


void	child_p(t_pipe *val)
{
	if (check_sq(val->argv[val->index], 0) == 0)
		ft_error(NULL, NULL, 2);
	val->cmd = ft_split(val->argv[val->index], ' ');
	if(!val->cmd)
		ft_error(NULL, "split faild", 4);
	val->path = ft_path(val->env);
	if(!val->path)
		ft_error(NULL, "path not found ", 4);
	val->exec = check_acss(val->path, val->cmd[0]);
	if(!val->exec)
		ft_error(NULL, val->cmd[0], 4);
	files_descriptor(val);
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
	if (val->index == val->argc - 2)
		close(val->tmp_in);
	else
		val->tmp_in = val->fd[0];
}

void	pipex(t_pipe *val)
{
	int	f;
	int	i;

	val->tmp_in = 0;
	i = val->index;
	while (val->index <= val->argc - 2)
	{
		if (val->index != val->argc - 2)
			pipe(val->fd);
		f = fork();
		if (f == 0)
			child_p(val);
		if (f > 0)
			parent_p(val);
		val->index++;
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

	if (!env || !*env)
		ft_error(NULL, NULL, 3);
	if (argc > 4)
	{
		if (ft_strcmp(argv[1], "here_doc") == 0)
		{
			// write(1, "herdoce", 7);
			val.index = 3;
			val.heredoc = 1;
		}
		else 
		{
			val.heredoc = 0;
			val.index = 2;
		}
		val.argc = argc;
		val.argv = argv;
		val.env = env;
		pipex(&val);
	}
	else
	{
		ft_putstr_fd("Error in argument\n", 2);
		exit(1);
	}
}
