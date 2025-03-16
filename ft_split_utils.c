/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:47:21 by ymouchta          #+#    #+#             */
/*   Updated: 2025/03/15 22:07:37 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *single_quote(const char *str, size_t *i)
{
    int start;
    int end;

    i++;
    start = *i;
    while(str[*i] != '\'')
        i++;
    end = *i;
    i++;
    printf("start  = %d\n", start);
    printf("end  = %d\n", end);
    return (ft_substr(str, start, end - start));
}
