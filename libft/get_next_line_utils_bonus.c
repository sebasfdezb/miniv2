/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:16:53 by sebferna          #+#    #+#             */
/*   Updated: 2025/01/08 16:43:16 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strchr_gnl(const char *str, int c)
{
	size_t	i;
	char	*s;
	char	*t;

	s = (char *)str;
	i = ft_strlen(s);
	t = s + i;
	while (s <= t)
	{
		if (*s == (char)c)
			return (1);
		s++;
	}
	return (0);
}

void	*ft_calloc_gnl(size_t count, size_t size)
{
	unsigned int	i;
	char			*memory;

	memory = (char *)malloc(count * size);
	if (memory == NULL)
		return (NULL);
	i = 0;
	while (i < (count * size))
	{
		memory[i] = '\0';
		i++;
	}
	return ((void *)memory);
}

void	*ft_memcpy_gnl(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	i = 0;
	d = (char *)dest;
	s = (const char *)src;
	if (!src && !dest)
		return (0);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}

char	*ft_strjoin_gnl(char *str1, char *str2)
{
	size_t	size1;
	size_t	size2;
	size_t	size3;
	char	*str3;
	int		i;

	if (str1 == NULL)
	{
		str1 = ft_calloc(1, sizeof(char));
		if (!str1)
			return (free(str1), str1 = NULL, NULL);
	}
	size1 = ft_strlen(str1);
	size2 = ft_strlen(str2);
	size3 = size1 + size2;
	i = size1;
	str3 = malloc(sizeof(char) * (size3 + 1));
	if (str3 == 0)
		return (free(str1), str1 = NULL, NULL);
	ft_memcpy(str3, str1, size1);
	ft_memcpy(&str3[i], str2, (size2 + 1));
	return (free(str1), str1 = NULL, str3);
}
