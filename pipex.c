/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:06:41 by ymouchta          #+#    #+#             */
/*   Updated: 2025/03/13 23:41:03 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h" 

int main(int argc, char **argv, char **env)
{
    t_pipe val;

    val.idex = 2;
    val.argc = argc;
    val.argv = argv;
    if(!env || !*env)
        ft_error(NULL, NULL, 3);
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
    pipex(&val);
}
