/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svetlana <svetlana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 22:28:00 by svydrina          #+#    #+#             */
/*   Updated: 2024/01/18 01:37:21 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

int	ft_strlen(char *s)
{
	int	i;

	i = -1;
	while (s[++i]);
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

void	ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

char *ft_strdup(char *s)
{
	char *dup;

	dup = malloc(ft_strlen(s) + 1);
	if (!dup)
		return (NULL);
	ft_strcpy(dup, s);
	return(dup);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int	len1;
	int	len2;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = malloc(len1 + len2 + 1);
	if (!new)
		return (NULL);
	ft_strcpy(new, s1);
	ft_strcpy(new + len1, s2);
	free(s1);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char	*line;
	char	*rest;
	int	bytes;
	int	index;

	line = ft_strdup(buf);
	while (!ft_strchr(line, '\n') && (bytes = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[bytes] = '\0';
		line = ft_strjoin(line, buf);
	}
	if (!ft_strlen(line))
		return (free(line), NULL);
	rest = ft_strchr(line, '\n');
	if (rest)
	{
		index = rest - line + 1;
		ft_strcpy(buf, rest + 1);
	}
	else
	{
		index = ft_strlen(line);
		ft_strcpy(buf, "");
	}
	line[index] = '\0';
	return (line);
}

#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	char	*line;
	int	fd;

	fd = open("test1.txt", O_RDONLY, 0644);
	printf("BUFFER_SIZE: %d\n", BUFFER_SIZE);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	return (0);
	
}
		
	

