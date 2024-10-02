/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hassende <hassende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:22:45 by hassende          #+#    #+#             */
/*   Updated: 2024/10/02 11:32:27 by hassende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define MAX_FD 1024
#define MAX_LEFT_SIZE 4096

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*set_line(char *line_buffer, char (*left_c)[MAX_LEFT_SIZE])
{
	size_t	i;
	char	*result;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == '\n')
		i++;
	result = ft_substr(line_buffer, 0, i);
	ft_strlcpy(*left_c, &line_buffer[i], MAX_LEFT_SIZE);
	free(line_buffer);
	return (result);
}

static char	*fill_line_buffer(int fd, char (*left_c)[MAX_LEFT_SIZE],
		char *buffer)
{
	ssize_t	b_read;
	char	*line;
	char	*tmp;

	line = ft_strdup(*left_c);
	(*left_c)[0] = '\0';
	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
		{
			free(line);
			return (NULL);
		}
		buffer[b_read] = '\0';
		tmp = line;
		line = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n') || b_read == 0)
			break ;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	left_c[MAX_FD][MAX_LEFT_SIZE];
	char		*line;
	char		*buffer;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = fill_line_buffer(fd, &left_c[fd], buffer);
	free(buffer);
	if (!line || *line == '\0')
	{
		free(line);
		return (NULL);
	}
	return (set_line(line, &left_c[fd]));
}

/*#include <stdio.h>
int main ()
{
	char *line;
	int fd = open ("black.txt", O_RDONLY);

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}

	close(fd);
	return(0);
}*/