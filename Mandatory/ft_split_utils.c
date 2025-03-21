/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:47:21 by ymouchta          #+#    #+#             */
/*   Updated: 2025/03/20 21:00:36 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*single_quote(char *str, size_t *i)
{
	int	start;
	int	end;

	*i += 1;
	start = *i;
	while (str[*i] != '\'')
		*i += 1;
	end = *i;
	*i += 1;
	return (ft_substr(str, start, end - start));
}
