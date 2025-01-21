/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:56:01 by sebferna          #+#    #+#             */
/*   Updated: 2025/01/21 18:06:40 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	lon;
	char	*s2;

	lon = ft_strlen(s);
	if (s == 0)
		return (0);
	if (start > lon)
		return (ft_strdup(""));
	if (lon < len + start)
		len = lon - start;
	s2 = malloc((len + 1) * sizeof(char));
	if (s2 == 0)
		return (0);
	ft_memcpy(s2, s + start, len);
	s2[len] = '\0';
	return (s2);
}

/* int	main(void)
{
	char	a[] = "Hola que tal";
	printf("%s", ft_substr(a, 3, 5));
	return (0);
} */