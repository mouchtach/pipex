/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:20:49 by ymouchta          #+#    #+#             */
/*   Updated: 2025/03/13 23:37:11 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

char    **ft_path(char **env)
{
    int i;
    int j;
    char *str = "PATH";
    i = 0;

    while(env[i])
    {
        j = 0;
        if(env[i][j] == str[j])
        {
            while (str[j] == env[i][j] && str[j]  && env[i][j])
                j++;
            if(str[j] == '\0')
                return (ft_split(env[i] + 5, ':'));
        }
        i++;
    }
    return NULL;
}

char *check_acss(char **path, char *cmd)
{
    int i = 0;
    char *join;
    char *tmp;

    while(path[i])
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

void  first_cmd(t_pipe *val)
{
    if(val->in == -1)
        ft_error(val, val->argv[val->idex - 1], 1);
    else
        dup2(val->in, 0);
}

void    last_cmd(t_pipe *val)
{
    if(val->out == -1)
        ft_error(val, val->argv[val->argc - 1], 1);
    else
        dup2(val->out, 1);
}

void    child_p(t_pipe *val, int i)
{
    val->cmd = ft_split(val->argv[val->idex], ' ');
    val->path = ft_path(val->env);
    val->exec = check_acss(val->path, val->cmd[0]);
    ft_free_path(val);
    if(val->idex == i)
        first_cmd(val);
    else
        dup2(val->tmp_in, 0);
    if (val->idex == val->argc - 2)
        last_cmd(val);
    else
        dup2(val->fd[1], 1);
    close(val->fd[0]);
    close(val->fd[1]);
    if(val->exec == NULL)
        ft_error(val, val->cmd[0], 0);
    if(execve(val->exec, val->cmd, NULL) == -1)
    {            
        free_all(val);
        free(val->exec);
    }
}

void    parent_p(t_pipe *val)
{
    close((*val).fd[1]);
    if ((*val).tmp_in != 0)
        close((*val).tmp_in);
    if((*val).idex == (*val).argc - 2)
        close((*val).tmp_in);
    else 
        (*val).tmp_in = (*val).fd[0];
}

void    pipex(t_pipe *val)
{
    int f;
    int i;

    val->tmp_in = 0;
    i = val->idex;
    while (val->idex <= val->argc - 2)
    {
        if(val->idex != val->argc - 2)
            pipe(val->fd);
        f = fork();
        if (f == 0)
            child_p(val, i);
        if (f > 0)
            parent_p(val);
        val->idex++;
    }
    while(wait(NULL) > 0);
    close (val->fd[0]);
    close (val->in);
    close (val->out);
}