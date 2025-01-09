/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:17:48 by sebferna          #+#    #+#             */
/*   Updated: 2025/01/08 16:54:21 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* static char	*ft_cleaner(char *str)
{
	int		i;
	int		j;
	char	*strtmp;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\0')
		return (free(str), NULL);
	strtmp = ft_calloc((ft_strlen_gnl(str) - i + 1), sizeof(char));
	if (!strtmp)
		return (free(str), NULL);
	i++;
	j = 0;
	while (str[i] != '\0')
		strtmp[j++] = str[i++];
	strtmp[j] = '\0';
	return (free(str), strtmp);
}

static char	*ft_line(char *str)
{
	int		i;
	char	*store;

	i = 0;
	if (str[i] == '\0')
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	store = ft_calloc((i + 1 + (str[i] == '\n')), sizeof(char));
	if (!store)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		store[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		store[i++] = '\n';
	store[i] = '\0';
	return (store);
}

static char	*ft_read(int fd, char *str)
{
	char	*store;
	int		read_char;

	read_char = 1;
	store = ft_calloc_gnl((BUFFER_SIZE + 1), sizeof(char));
	if (!store)
		return (free(str), NULL);
	while (read_char > 0 && !ft_strchr(store, '\n'))
	{
		read_char = read(fd, store, BUFFER_SIZE);
		if (read_char < 0)
			return (free(store), NULL);
		store[read_char] = '\0';
		str = ft_strjoin(str, store);
		if (!str)
			return (free(str), free(store), NULL);
	}
	return (free(store), str);
}

char	*get_next_line(int fd)
{
	static char	*str[2048];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) < 0)
	{
		if (str[fd] != NULL)
		{
			free(str[fd]);
			str[fd] = NULL;
		}
		return (NULL);
	}
	str[fd] = ft_read(fd, str[fd]);
	if (!str[fd])
		return (free(str[fd]), str[fd] = NULL, NULL);
	line = ft_line(str[fd]);
	if (!line)
		return (free(str[fd]), str[fd] = NULL, NULL);
	str[fd] = ft_cleaner(str[fd]);
	if (!str[fd])
		return (free(str[fd]), str[fd] = NULL, line);
	return (line);
} */

static char	*read_fd(int fd, char *buffer)
{
	char	*buffer_aux;
	int		i;

	buffer_aux = ft_calloc_gnl ((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer_aux)
		return (free (buffer), buffer = NULL, NULL);
	i = 1;
	while (i > 0 && !ft_strchr_gnl (buffer_aux, '\n'))
	{
		i = read(fd, buffer_aux, BUFFER_SIZE);
		if (i < 0)
			return (free (buffer), buffer = NULL, free (buffer_aux),
				buffer_aux = NULL, NULL);
		buffer_aux[i] = '\0';
		buffer = ft_strjoin_gnl(buffer, buffer_aux);
		if (!buffer)
			return (free (buffer), buffer = NULL, free (buffer_aux),
				buffer_aux = NULL, NULL);
	}
	return (free (buffer_aux), buffer_aux = NULL, buffer);
}

static char	*get_line_f(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (buffer[i] == '\0')
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	line = ft_calloc_gnl ((i + 1 + (buffer[i] == '\n')), sizeof(char));
	if (!line)
		return (NULL);
	if (buffer[i] != '\0')
		line[i + 1] = '\0';
	while (i >= 0)
	{
		line[i] = buffer[i];
		i--;
	}
	return (line);
}

static char	*get_rest(char *buffer)
{
	char	*rest_line;
	int		i;
	int		j;
	size_t	len;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\0')
		return (free (buffer), buffer = NULL, NULL);
	len = ft_strlen_gnl(buffer);
	rest_line = ft_calloc_gnl (((len - i) + 1), sizeof(char));
	if (!rest_line)
		return (free (buffer), buffer = NULL, NULL);
	i++;
	j = 0;
	while (buffer[i] != '\0')
	{
		rest_line[j] = buffer[i];
		i++;
		j++;
	}
	rest_line[j] = buffer[i];
	return (free (buffer), buffer = NULL, rest_line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, NULL, 0) < 0)
	{
		if (buffer[fd] != NULL)
		{
			free(buffer[fd]);
			buffer[fd] = NULL;
		}
		return (NULL);
	}
	buffer[fd] = read_fd(fd, buffer[fd]);
	if (!buffer[fd])
		return (free (buffer[fd]), buffer[fd] = NULL, NULL);
	line = get_line_f(buffer[fd]);
	if (!line)
		return (free (buffer[fd]), buffer[fd] = NULL, NULL);
	buffer[fd] = get_rest(buffer[fd]);
	if (!buffer[fd])
		return (free (buffer[fd]), buffer[fd] = NULL, line);
	return (line);
}
