/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hassende <hassende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:12:52 by hassende          #+#    #+#             */
/*   Updated: 2024/10/01 14:29:31 by hassende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

#define MAX_FD 16

static char	*set_line(char *line_buffer, char (*left_c)[BUFFER_SIZE])
{
	size_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == 0 || line_buffer[1] == 0)
		return (NULL);
	ft_strlcpy(*left_c, &line_buffer[i + 1], BUFFER_SIZE);
	if ((*left_c)[0] == 0)
	{
		(*left_c)[0] = '\0';
	}
	line_buffer[i + 1] = '\0';
	return (line_buffer);
}

static char	*fill_line_buffer(int fd, char (*left_c)[BUFFER_SIZE], char *buffer)
{
	ssize_t	b_read;
	char	*line;
	char	*tmp;

	line = ft_strdup(*left_c);
	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
		{
			free(line);
			return (NULL);
		}
		else if (b_read == 0)
			break ;
		buffer[b_read] = '\0';
		tmp = line;
		line = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	left_c[MAX_FD][BUFFER_SIZE];
	char		*line;
	char		*buffer;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = fill_line_buffer(fd, &left_c[fd], buffer);
	free(buffer);
	if (!line)
	{
		left_c[fd][0] = '\0';
		return (NULL);
	}
	return (set_line(line, &left_c[fd]));
}

/*#include <stdio.h>
int main ()
{
	int fd = open("black.txt", O_RDONLY);
	int fd2 = open("white.txt", O_RDONLY);
	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
		while ((line = get_next_line(fd2)) != NULL)
		{
			printf("%s", line);
			free(line);
		}
	}
	close (fd);
	close (fd2);

	return (0);
}*/
