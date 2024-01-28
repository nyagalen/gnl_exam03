/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 01:08:31 by svydrina          #+#    #+#             */
/*   Updated: 2024/01/17 21:13:52 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
}

void	ft_strcpy(char *s1, char *s2)
{
	int 	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int	len1;
	int	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = malloc(len1 + len2 + 1);
	if (!new)
		return (NULL);
	ft_strcpy(new, s1);
	ft_strcpy((new + len1), s2);
	free(s1);
	return (new);
}

char	*ft_strdup(char *s)
{
	char	*new;
	int		len;

	len = ft_strlen(s) + 1;
	new = malloc(len);
	if (!new)
		return (NULL);
	ft_strcpy(new, s);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char	*res;
	char	*rest;
	int		bytes;
	int		index;

	res = ft_strdup(buf);
	while (!(ft_strchr(res, '\n')) && (bytes = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[bytes] = '\0';
		res = ft_strjoin(res, buf);
	}
	if (!ft_strlen(res))
		return (free(res), NULL);
	rest = ft_strchr(res, '\n');
	if (rest)
	{
		index = rest - res + 1;
		rest = rest + 1;
		ft_strcpy(buf, rest);
	}
	else
	{
		ft_strcpy(buf, "");
		index = ft_strlen(res);
	}
	res[index] = '\0';
	return (res);
}

#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int	fd;
	char *line;

	fd = open("test1.txt", O_RDONLY, 0644);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}



