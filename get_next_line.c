/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hassende <hassende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:28:34 by hassende          #+#    #+#             */
/*   Updated: 2024/09/18 15:09:59 by hassende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*function_name(int fd, char *buf, char **backup)
{
	int		read_line;
	char	*char_temp;

	while (1)
	{
		read_line = read(fd, buf, BUFFER_SIZE);
		if (read_line == -1)
			return (NULL);
		if (read_line == 0)
			break ;
		buf[read_line] = '\0';
		if (!backup[fd])
			backup[fd] = ft_strdup("");
		char_temp = backup[fd];
		backup[fd] = ft_strjoin(char_temp, buf);
		free(char_temp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (backup[fd]);
}

static char	*extract(char *line)
{
	size_t	count;
	char	*backup;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0')
	{
		free(line);
		return (NULL);
	}
	backup = ft_substr(line, count + 1, ft_strlen(line) - count - 1);
	line[count + 1] = '\0';
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*backup[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = function_name(fd, buffer, backup);
	free(buffer);
	if (!line)
		return (NULL);
	backup[fd] = extract(line);
	return (line);
}

// int	main(void)
// {
// 	int fd = open("black.txt", O_RDONLY);
// 	char *line;

// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		 printf("\nThe printed line: %s\n", line);
// 		 free(line);
// 	}
// 	// line = get_next_line(fd);
// 	// printf("\nThe printed line: %s\n", line);
// 	// free(line);
// 	// char *line2 = get_next_line(fd);
// 	// printf("\nThe printed line2: %s\n", line2);
// 	// free(line2);
// 	close(fd);
// 	return (0);
// }