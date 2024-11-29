/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agragera <agragera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:56:47 by agragera          #+#    #+#             */
/*   Updated: 2024/03/29 20:14:41 by logname          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*strjoin_and_free(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*new_str;
	size_t	i;
	size_t	j;

	len1 = 0;
	len2 = 0;
	while (s1 && s1[len1])
		len1++;
	while (s2 && s2[len2])
		len2++;
	new_str = (char *)malloc(len1 + len2 + 1);
	if (!new_str)
		return (NULL);
	i = -1;
	while (++i < len1)
		new_str[i] = s1[i];
	j = -1;
	while (++j < len2)
		new_str[i + j] = s2[j];
	new_str[i + j] = '\0';
	free(s1);
	return (new_str);
}

char	*copy_and_advance(char *dest, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*extract_line(char **storage)
{
	size_t	len;
	char	*line;
	char	*temp;

	len = 0;
	while ((*storage)[len] && (*storage)[len] != '\n')
		len++;
	if ((*storage)[len] == '\n')
		len++;
	line = (char *)malloc(len + 1);
	if (!line)
		return (NULL);
	copy_and_advance(line, *storage, len);
	temp = (char *)malloc(ft_strlen(*storage + len) + 1);
	if (!temp)
		return (free(line), NULL);
	copy_and_advance(temp, *storage + len, ft_strlen(*storage + len));
	free(*storage);
	*storage = temp;
	return (line);
}

char	*read_line(int fd, char **storage)
{
	char	*buffer;
	int		bytes_read;

	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(*storage, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			*storage = strjoin_and_free(*storage, buffer);
			if (!*storage)
				return (free(buffer), NULL);
		}
	}
	free(buffer);
	if (bytes_read == -1 || (!bytes_read && !**storage))
		return (free(*storage), *storage = NULL, NULL);
	return (extract_line(storage));
}

char	*get_next_line(int fd)
{
	static char	*storage[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	if (!storage[fd])
		storage[fd] = (char *)ft_calloc(1, sizeof(char));
	return (read_line(fd, &storage[fd]));
}
