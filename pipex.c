/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:06:41 by ymouchta          #+#    #+#             */
/*   Updated: 2025/03/11 23:35:11 by ymouchta         ###   ########.fr       */
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

    while(path[i])
    {
        join = ft_strjoin("/", cmd);
        join = ft_strjoin(path[i], join);
        if (access(join, X_OK) == 0)
            return (join);
        free(join);
        i++;
    }
    return (NULL);
}

void ft_error(char *str, int i)
{
    if(i == 0)
    {
        ft_putstr_fd("command not found: ", 2);
        ft_putstr_fd(str, 2);
    }
    else if (i == 1)
    {
        ft_putstr_fd("no such file or directory: ", 2);
        ft_putstr_fd(str, 2);
    } 
    else
        ft_putstr_fd("envirement variable doesn\'t exist ", 2);
    write(2, "\n", 1);
    exit(1);
}
void    child_p(t_pipe val, int i)
{
    char *exec;
    char **path;

    path = ft_path(val.env);
    exec = check_acss(path, val.cmd[0]);
    if (val.idex == i)
    {
        if(val.in == -1)
            ft_error(val.argv[val.idex], 1);
        dup2(val.in, 0);
        dup2(val.fd[1], 1);
    }
    else if(val.idex == val.argc - 2)
    {
        dup2(val.out, 1);        
        dup2(val.tmp_in, 0);        
    }
    else 
    {
        dup2(val.fd[1], 1);
        dup2(val.tmp_in, 0);
    }
    close(val.fd[0]);
    close(val.fd[1]);
    
    if(execve(exec, val.cmd, NULL) == -1)
        ft_error(val.cmd[0], 0);
}

void       parent_p(t_pipe *val)
{
    close((*val).fd[1]);
    if ((*val).tmp_in != 0)
        close((*val).tmp_in);
    if((*val).idex == (*val).argc - 2)
        close((*val).tmp_in);
    else 
        (*val).tmp_in = (*val).fd[0];
}

void pipex(t_pipe val)
{
    char *exec;
    int f;
    int i;

    val.tmp_in = 0;
    i = val.idex;
    while (val.idex <= val.argc - 2)
    {
        val.cmd = ft_split(val.argv[val.idex], ' ');    
        pipe(val.fd);
        f = fork();
        if (f == 0)
            child_p(val, i);
        if (f > 0)
        {
            parent_p(&val);
        }    
        val.idex++;
    }
    while(wait(NULL) > 0);
    close (val.in);
    close (val.fd[0]);
    close (val.out);
}


#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv, char **env)
{
    t_pipe val;

    val.idex = 2;
    val.argc = argc;
    val.argv = argv;
    // if(!env || !*env)
    //     ft_error(NULL, 3);
    if(argc < 5)
    {
        ft_putstr_fd("Error in argument\n", 2);
        exit(1);
    }
    if (ft_strcmp(argv[1], "heredoc") == 0)
    {
        val.in = heredoc(argv[2]);
        val.idex = 3;
    }
    else 
        val.in = open(argv[1], O_RDWR, 0777);
    val.out = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
    val.env = env;
    pipex(val);    
}
