/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hassende <hassende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:13:07 by hassende          #+#    #+#             */
/*   Updated: 2024/09/25 11:55:29 by hassende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strchr(char *s, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *)&s[i]);
	return (NULL);
}

static char	*set_line(char *line_buffer)
{
	char	*rem;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == '\0')
		return (NULL);
	rem = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*rem == 0)
	{
		free(rem);
		rem = NULL;
	}
	line_buffer[i + 1] = '\0';
	return (rem);
}

static char	*fill_line_buffer(int fd, char *rem, char *buffer)
{
	ssize_t	b_read;
	char	*tmp;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read < 0)
		{
			free(rem);
			return (NULL);
		}
		else if (b_read == 0)
			break ;
		buffer[b_read] = '\0';
		if (!rem)
			rem = ft_strdup("");
		tmp = rem;
		rem = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (rem);
}

char	*get_next_line(int fd)
{
	static char	*rem;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = fill_line_buffer(fd, rem, buffer);
	free(buffer);
	if (!line)
	{
		rem = NULL;
		return (NULL);
	}
	rem = set_line(line);
	return (line);
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
	}
	close (fd);
	close (fd2);

	return (0);
}*/
