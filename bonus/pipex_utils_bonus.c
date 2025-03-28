/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:20:49 by ymouchta          #+#    #+#             */
/*   Updated: 2025/03/25 00:39:32 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	command_exist(t_pipe *val)
{
	char	**cmd;

	if (access(val->argv[val->index], X_OK) == 0)
	{
		cmd = ft_split(val->argv[val->index], ' ');
		if (execve(val->argv[val->index], cmd, NULL) == -1)
			ft_error(val, "execve faild", 2);
	}
}

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

void	child_p(t_pipe *val)
{
	val->exec = NULL;
	val->cmd = NULL;
	val->path = NULL;
	files_descriptor(val);
	command_exist(val);
	if (check_sq(val->argv[val->index], 0) == 0)
		ft_error(NULL, "awk: syntax error", 2);
	val->cmd = ft_split(val->argv[val->index], ' ');
	if (!val->cmd)
		ft_error(NULL, "split faild", 2);
	val->path = ft_path(val->env);
	if (!val->path)
		ft_error(val, "path not found ", 2);
	val->exec = check_acss(val->path, val->cmd[0]);
	if (!val->exec)
		ft_error(val, val->cmd[0], 0);
	ft_free_path(val);
	if (execve(val->exec, val->cmd, NULL) == -1)
		ft_error(val, "execve faild", 2);
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
