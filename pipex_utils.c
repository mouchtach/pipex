/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:20:49 by ymouchta          #+#    #+#             */
/*   Updated: 2025/03/18 19:45:31 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	first_cmd(t_pipe *val)
{
	if (val->in == -1)
		ft_error(val, val->argv[val->idex - 1], 1);
	else
		dup2(val->in, 0);
	dup2(val->fd[1], 1);
}

void	last_cmd(t_pipe *val)
{
	if (val->out == -1)
		ft_error(val, val->argv[val->argc - 1], 1);
	else
		dup2(val->out, 1);
	dup2(val->fd[0], 0);
}
