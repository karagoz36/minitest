/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkaragoz <tkaragoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:05:13 by tkaragoz          #+#    #+#             */
/*   Updated: 2024/07/17 16:34:31 by tkaragoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

static char	*ft_new_remainder(char *remainder)
{
	char	*n_remainder;
	int		i;
	int		j;
	int		len;

	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (!remainder[i])
		return (free(remainder), NULL);
	len = ft_strlen(remainder);
	n_remainder = ft_calloc((len - i + 1), 1);
	if (!n_remainder)
		return (free(remainder), NULL);
	i++;
	j = 0;
	while (remainder[i])
		n_remainder[j++] = remainder[i++];
	return (free(remainder), n_remainder);
}

static char	*get_line(char *remainder)
{
	char	*line;
	int		i;

	if (!remainder[0])
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	line = ft_calloc((i + 2), 1);
	if (!line)
		return (NULL);
	i = 0;
	while (remainder[i])
	{
		line[i] = remainder[i];
		i++;
		if (line[i - 1] == '\n')
			break ;
	}
	return (line);
}

static char	*ft_read_buffer(int fd, char *remainder)
{
	int			bytes_read;
	int			i;
	char		*buffer;

	buffer = ft_calloc((BUFFER_SIZE + 1), 1);
	if (!buffer)
		return (free(remainder), NULL);
	while (!ft_strchr(remainder, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		else if (bytes_read == -1)
			return (free(buffer), free(remainder), NULL);
		remainder = ft_gnljoin(remainder, buffer);
		if (!remainder)
			return (NULL);
		i = 0;
		while (i <= BUFFER_SIZE)
			buffer[i++] = '\0';
	}
	return (free(buffer), remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE < 0)
		return (free(remainder), NULL);
	remainder = ft_read_buffer(fd, remainder);
	if (!remainder)
		return (NULL);
	line = get_line(remainder);
	remainder = ft_new_remainder(remainder);
	if (!remainder)
	{
		if (ft_strlen(line))
			return (line);
		return (free(line), NULL);
	}
	return (line);
}

int	main(void)
{
	int		fd;
	// int		fd2;
	char	*buffer;

	fd = open("a.txt", O_RDONLY);
	//fd2 = open("b.txt", O_RDONLY);
	buffer = get_next_line(fd);
	//free(buffer);
	//buffer = get_next_line(fd2);
	// free(buffer);
	// while ((buffer))
	// {
	// 	printf("%s", buffer);
	// 	free(buffer);
	// 	buffer = get_next_line(fd);
	// }
	free(buffer);
	buffer = get_next_line(-1);
	close(fd);
	// close(fd2);
	return (0);
}
