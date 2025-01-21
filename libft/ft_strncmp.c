/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:37:40 by sebferna          #+#    #+#             */
/*   Updated: 2025/01/21 18:05:33 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char *st1;
	unsigned char *st2;

	i = 0;
	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (st1[i] != '\0' && st2[i] != '\0' && (i < n - 1) && st1[i] == st2[i])
		i++;
	return (st1[i] - st2[i]);
}

/* int	main(void)
{
	const char s1[4] = "Hola";
	const char s2[5] = "Holaa";
	size_t n = 5;
	printf("%d", ft_strncmp(s1, s2, n));
	return (0);
} */
