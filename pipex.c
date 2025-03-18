/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:43:51 by ymouchta          #+#    #+#             */
/*   Updated: 2025/03/18 01:42:45 by ymouchta         ###   ########.fr       */
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

void    child_process(t_pipe *val)
{
    if (check_sq(val->argv[val->index], 0) == 0)
		ft_error(NULL, NULL, 2);
	val->cmd = ft_split(val->argv[val->index], ' ');
	val->path = ft_path(val->env);
	val->exec = check_acss(val->path, val->cmd[0]);
    // printf("cmd = %s\n", val->cmd[0]);  
    // printf("path = %s\n", val->path[0]);  
    // printf("exec = %s\n", val->exec);  
    // exit(0);
    if(val->index == 2)
        ft_first(val);
    if(val->index == 3)
        ft_last(val);
    close(val->fd[0]);
	close(val->fd[1]);
    if (val->exec == NULL)
		ft_error(val, val->cmd[0], 0);
    ft_free_path(val);
	if (execve(val->exec, val->cmd, NULL) == -1)
	{
		free_all(val);
		free(val->exec);
	}
}

void    pipex(t_pipe *val)
{
    int child;

    pipe(val->fd);
    while (val->index < val->argc - 1)
    {
        child = fork();
        if(child < 0)
            ft_error(NULL, NULL, 4);
        if(child == 0)    
            child_process(val);
        val->index++;
        
    }
    wait(NULL);
    wait(NULL);
    close(val->fd[0]);
    close(val->fd[1]);
    close(val->in);
    close(val->out);
}

int	main(int argc, char **argv, char **env)
{
    t_pipe val;

    if (!env || !*env)
		ft_error(NULL, NULL, 3);
    if(argc == 5)
    {
        val.in = open(argv[1], O_RDONLY, 0777);
        val.out = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
        val.argv = argv;
        val.argc = argc;
        val.env = env;
        val.index = 2;
        pipex(&val);  
    }
    else 
    {
        ft_putstr_fd("Error in argument\n", 2);
		exit(1);
    }
}
