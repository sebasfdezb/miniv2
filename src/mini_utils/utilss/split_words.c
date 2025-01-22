/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:24:14 by sebferna          #+#    #+#             */
/*   Updated: 2025/01/22 15:29:10 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	counter_continue(t_data *d, char const *s, char c, int *count)
{
	if (*s != '\0' && *s != d->qte && *s != c)
		(*count)++;
}

int	count_words(t_data *d, char const *s, char c, int count)
{
	while (*s != '\0')
	{
		d->qte = '\0';
		while ((*s == c || *s == 39 || *s == 34) && *s != d->qte && *s != '\0')
		{
			if (d->flag == 0 && (*s == '\'' || *s == '\"'))
			{
				d->flag = !d->flag;
				d->qte = *s;
			}
			if (++s && *s != '\0' && *s == d->qte)
				break ;
		}
		counter_continue(d, s, c, &count);
		if (d->flag)
		{
			while (*s != d->qte && *s != '\0')
				s++;
			d->flag = !d->flag;
		}
		while (*s != c && *s != '\0' && *(s)++)
			if (*s == '\'' || *s == '\"')
				break ;
	}
	return (count);
}

int	size_words(t_data *da, char const *s, char c, int *d)
{
	while (s[*d] != '\0' && s[*d] != c)
	{
		while ((s[*d] == '\'' || s[*d] == '\"') && s[(*d) + 1] == s[*d]
			&& ++(*d) && ++(*d))
			while (s[*d] == c)
				(*d)++;
		while ((s[*d] == 39 || s[*d] == 34) && da->qte == '\0' && s[*d] != '\0')
		{
			if (da->qte == '\0' || s[*d] == da->qte)
			{
				da->flag = !da->flag;
				da->qte = s[*d];
			}
			(*d)++;
			while (!da->flag && s[*d] == c)
				(*d)++;
		}
		while ((da->flag || s[*d] != c) && s[*d] != da->qte
			&& s[*d] != '\0' && ++(*d) && ++da->size)
			if (!da->flag && (s[*d] == '\'' || s[*d] == '\"'))
				return (da->size);
		if (s[*d] == da->qte)
			return (da->size);
	}
	return (da->size);
}

void	split_words(t_data *data, char const *str, char c)
{
	if (str[data->d] != c)
	{
		if (str[data->d] == data->qte && data->flag == 1)
			data->d++;
		while (str[data->d] == c)
			data->d++;
	}
	while (str[data->d] == c)
		data->d++;
}
