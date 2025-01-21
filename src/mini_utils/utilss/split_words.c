/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:24:14 by sebferna          #+#    #+#             */
/*   Updated: 2025/01/21 15:35:49 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	counter_continue(t_data *d, char const *s, char c, int *count)
{
	if (*s != '\0' && *s != d->quote && *s != c)
		(*count)++;
}

int	count_words(t_data *d, char const *s, char c, int count)
{
	while (*s != '\0')
	{
		d->quote = '\0';
		while ((*s == c || *s == 39 || *s == 34) && *s != d->quote && *s != '\0')
		{
			if (d->flag == 0 && (*s == '\'' || *s == '\"'))
			{
				d->flag = !d->flag;
				d->quote = *s;
			}
			if (++s && *s != '\0' && *s == d->quote)
				break ;
		}
		counter_continue(d, s, c, &count);
		if (d->flag)
		{
			while (*s != d->quote && *s != '\0')
				s++;
			d->flag = !d->flag;
		}
		while (*s != c && *s != '\0' && *(s)++)
			if (*s == '\'' || *s == '\"')
				break ;
	}
	return (count);
}

int	size_words(t_data *data, char const *s, char c, int *d)
{
	while (s[*d] != '\0' && s[*d] != c)
	{
		while ((s[*d] == '\'' || s[*d] == '\"') && s[(*d) + 1] == s[*d]
			&& ++(*d) && ++(*d))
			while (s[*d] == c)
				(*d)++;
		while ((s[*d] == 39 || s[*d] == 34) && data->quote == '\0' && s[*d] != '\0')
		{
			if (data->quote == '\0' || s[*d] == data->quote)
			{
				data->flag = !data->flag;
				data->quote = s[*d];
			}
			(*d)++;
			while (!data->flag && s[*d] == c)
				(*d)++;
		}
		while ((data->flag || s[*d] != c) && s[*d] != data->quote && s[*d] != '\0'
			&& ++(*d) && ++data->size)
			if (!data->flag && (s[*d] == '\'' || s[*d] == '\"'))
				return (data->size);
		if (s[*d] == data->quote)
			return (data->size);
	}
	return (data->size);
}

void	split_words(t_data *data, char const *str, char c)
{
	if (str[data->d] != c)
	{
		if (str[data->d] == data->quote && data->flag == 1)
			data->d++;
		while (str[data->d] == c)
			data->d++;
	}
	while (str[data->d] == c)
		data->d++;
}
