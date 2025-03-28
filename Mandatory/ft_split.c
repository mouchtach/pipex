/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:21:30 by ymouchta          #+#    #+#             */
/*   Updated: 2025/03/20 21:00:05 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**freep(char **p, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (NULL);
}

static size_t	countwords(char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '\'' && check_sq(s, i))
		{
			i++;
			while (s[i] != '\'')
				i++;
			count++;
			i++;
		}
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static char	**pcpy(char *s, char **p, char c, size_t x)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (j < x && s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\'' && check_sq(s, i))
			p[j++] = single_quote(s, &i);
		else
		{
			start = i;
			while (s[i] != c && s[i])
				i++;
			p[j++] = ft_substr(s, (unsigned int)start, i - start);
		}
		if (!p[j - 1])
			return (freep(p, j));
	}
	p[j] = NULL;
	return (p);
}

char	**ft_split(char *s, char c)
{
	char	**p;
	size_t	count;

	if (!s)
		return (NULL);
	count = countwords(s, c);
	p = (char **)malloc(sizeof(char *) * (count + 1));
	if (!p)
		return (NULL);
	return (pcpy(s, p, c, count));
}
