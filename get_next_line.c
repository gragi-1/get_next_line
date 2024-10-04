/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agragera <agragera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:55:54 by agragera          #+#    #+#             */
/*   Updated: 2024/03/25 17:55:54 by agragera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*update_static_storage(char *stat_str)
{
	char	*new_str;
	int		i;

	i = 0;
	while (stat_str[i] && stat_str[i] != '\n')
		i++;
	if (!stat_str[i])
	{
		free(stat_str);
		return (NULL);
	}
	new_str = ft_strdup(stat_str + i + 1);
	free(stat_str);
	return (new_str);
}

static char	*extract_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static int	read_from_fd(int fd, char **stat_str)
{
	char	*buff;
	char	*temp;
	int		read_bytes;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (-1);
	read_bytes = 1;
	while (!ft_strchr(*stat_str, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			return (-1);
		}
		buff[read_bytes] = '\0';
		temp = *stat_str;
		*stat_str = ft_strjoin(temp, buff);
		free(temp);
	}
	free(buff);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*stat_str = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read_from_fd(fd, &stat_str) == -1)
		return (NULL);
	line = extract_line(stat_str);
	stat_str = update_static_storage(stat_str);
	return (line);
}
