/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:06:41 by ymouchta          #+#    #+#             */
/*   Updated: 2025/03/11 02:25:09 by ymouchta         ###   ########.fr       */
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
#include <stdio.h>

void    child_p(t_pipe val, int i)
{

    if (val.idex == i)
    {
        dup2(val.in, 0);
    }
    else 
    {
        
        close(val.fd[1]);
        char *line = get_next_line(val.fd[0]);
        if(!line)
        {
            printf("hhhhhh\n");
            exit(0);
        }
        while(line)
        {
            printf("%s", line);
            line = get_next_line(val.fd[0]);
        }
        close(val.fd[0]);
    }
        
    if(val.idex != val.argc - 2)
        dup2(val.fd[1], 1);
    else 
        dup2(val.out, 1);

    close(val.fd[0]);
    execve(val.path, val.cmd, NULL);
}

void pipex(t_pipe val)
{
    char **path;
    char *exec;
    int f;
    int i;

    i = val.idex;
    path =  ft_path(val.env);
    while (val.idex <= val.argc - 2)
    {
        val.cmd = ft_split(val.argv[val.idex], ' ');
        exec = check_acss(path, val.cmd[0]);
        if(!exec)
        {
            write(2, "command not found\n", 18);
            exit(1);
        }
        val.path = exec;
        pipe(val.fd);
        f = fork();
        if (f == 0)
            child_p(val, i);
        if (f > 0)
        {
            close(val.fd[1]);
            close(val.fd[0]);
        }    
        val.idex++;
    }
    while(wait(NULL) > 0);
    close (val.in);
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
    val.hrd = 0;
    if(argc < 5)
    {
        write(2, "Error\n", 6);
        exit(1);
    }
    if (ft_strcmp(argv[1], "heredoc") == 0)
    {
        val.in = heredoc(argv[2]);
        val.idex = 3;
        val.hrd = 1;
    }
    else 
        val.in = open(argv[1], O_RDWR, 0777);
    val.out = open(argv[argc - 1], O_CREAT | O_RDWR, 0777);
    val.env = env;
    pipex(val);    
}
