/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:00:46 by sebferna          #+#    #+#             */
/*   Updated: 2025/01/20 16:41:40 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	input_files(t_data *d, t_parser **node, int *i, int *j)
{
	while (d->cmd[*i][*j] != '\0')
	{
		d->size = 0;
		d->a = -1;
		while (d->cmd[*i][*j] != ' ' && d->cmd[*i][*j]!= '\0' && ++(d->size))
			(*j)++;
		d->filein = ft_calloc(d->size + 1, sizeof(char));
		d->size = (*j) - d->size;
		while (d->cmd[*i][d->size] != ' ' && d->cmd[*i][d->size] != '\0')
		{
			d->filein[++(d->a)] = d->cmd[*i][d->size];
			(d->size)++;
		}
		if ((*node)->filein != 0)
			close((*node)->filein);
		(*node)->filein = open(d->filein, O_RDONLY);
		free(d->filein);
		if ((*node)->filein == -1)
			return (close((*node)->filein), printf("error"));
		while (d->cmd[*i][*j] == ' ')
			(*j)++;
	}
	return (EXIT_SUCCESS);
}

int	process_command(t_data *data, t_parser **node, int *i)
{
	data->b = 0;
	data->str = ft_calloc((data->size) + 1, sizeof(char));
	while (data->cmd[*i][data->a] != '<' && data->cmd[*i][data->a] != '>' &&
			data->cmd[*i][data->a] != '\0')
	{
		if (data->cmd[*i][data->a] == data->quote)
		{
			data->str[data->b] = data->cmd[*i][data->a];
			(data->a)++;
			(data->b)++;
			while (data->cmd[*i][data->a] != data->quote)
			{
				data->str[data->b] = data->cmd[*i][data->a];
				(data->a)++;
				(data->b)++;
			}
		}
		data->str[data->b] = data->cmd[*i][data->a];
		(data->a)++;
		(data->b)++;
	}
	(*node)->all_cmd = get_words(data, data->str, ' ', -1);
	if (!(*node)->all_cmd)
		return (free(data->str), data->str = NULL, EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_command(t_data *data, t_parser **node, int *i, int *j)
{
	if (data->cmd[*i][*j] != ' ' && data->cmd[*i][*j] != '\0' &&
		data->cmd[*i][*j] != '>' && data->cmd[*i][*j] != '<')
	{
		data->size = 0;
		data->a = *j;
		while (data->cmd[*i][*j] != '<' && data->cmd[*i][*j] != '>' &&
				data->cmd[*i][*j] != '\0')
		{
			if (data->cmd[*i][*j] == '\'' || data->cmd[*i][*j] == '\"')
			{
				data->quote = data->cmd[*i][*j];
				(data->size)++;
				while (data->cmd[*i][++(*j)] != data->quote)
					(data->size)++;
			}
			(data->size)++;
			(*j)++;
		}
		if (process_command(data, node, i) == 1)
			return (EXIT_FAILURE);
	}
	free(data->str);
	data->str = NULL;
	return (EXIT_SUCCESS);
}

int	get_tokens(t_data *data, t_parser **node, int *i, int *j)
{
	while (data->cmd[*i][*j] == '<' || data->cmd[*i][*j] == '>')
	{
		if ((*node)->filein != 0 && data->cmd[*i][*j] == '<')
			close((*node)->filein);
		if ((*node)->fileout != 1 && data->cmd[*i][*j] == '>')
			close((*node)->fileout);
		if (get_token_filein(data, node, i, j) == 1)
			return (EXIT_FAILURE);
		if (get_token_fileout(data, node, i, j) == 1)
			return (EXIT_FAILURE);
	}
	data->size = 0;
	data->a = -1;
	return (EXIT_SUCCESS);
}

int	parsing(t_data *data, int i, int j)
{
	while (data->cmd[i] != NULL)
	{
		j = 0;
		if (data->cmd[i][j] == '\0')
			return (EXIT_FAILURE);
		while (data->cmd[i][j] != '\0')
		{
			data->node = ft_calloc(1, sizeof(t_parser));
			data->node->fileout = 1;
			data->node->filein = 0;
			while (data->cmd[i][j] == ' ')
				j++;
			if (get_tokens(data, &data->node, &i, &j) == 1)
				return (free_t_parser(data->node), EXIT_FAILURE);
			if (get_command(data, &data->node, &i, &j) == 1)
				return (free_t_parser(data->node), EXIT_FAILURE);
			if (get_tokens(data, &data->node, &i, &j) == 1)
				return (free_t_parser(data->node), EXIT_FAILURE);
			if (input_files(data, &data->node, &i, &j) == 1)
				return (free_t_parser(data->node), EXIT_FAILURE);
		}
		ft_lstadd_back(&data->nodes, ft_lstnew(data->node));
		i++;
	}
	return (EXIT_SUCCESS);
}
