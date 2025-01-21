/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 14:30:27 by sebferna          #+#    #+#             */
/*   Updated: 2025/01/21 18:01:44 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*s2;

	len = ft_strlen(s1) + 1;
	s2 = malloc(len * sizeof(char));
	if (s2 == 0)
		return (0);
	ft_memcpy(s2, s1, len);
	return (s2);
}

/* int	main(void)
{
	char	s1[] = "Holaaa";
	printf("%s", ft_strdup(s1));
	return (0);
} */
