/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 23:28:28 by ymouchta          #+#    #+#             */
/*   Updated: 2025/03/11 00:44:25 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

int heredoc(char *dlm)
{

    char *line;
    int herdoc;

    herdoc = open("heredoc", O_CREAT | O_RDWR | O_APPEND, 0777);
    dlm = ft_strjoin(dlm, "\n");
    while (1)
    {
        write(1, "heredoc>", 8);
        line = get_next_line(STDIN_FILENO);
        if (ft_strcmp(line , dlm) == 0)
            break;
        ft_putstr_fd(line, herdoc);
        free(line);
    }
    free(line);
    close(herdoc);
    herdoc = open("heredoc", O_RDONLY, 0777);
    return (herdoc);
}
