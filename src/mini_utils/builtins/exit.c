/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:58:27 by sebferna          #+#    #+#             */
/*   Updated: 2025/01/08 17:51:35 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* int	ex_exit(t_data *data, t_parser *node, int i, int fd)
{
	ft_printf(fd, "exit\n");
	if (node->all_cmd[1] != NULL && node->all_cmd[2] != NULL)
		return (ft_printf(fd, "exit: too many arguments\n"));
	else if (node->all_cmd[1] != NULL)
	{
		i = -1;
		if (node->all_cmd[1][0] == '+' || node->all_cmd[1][0] == '-')
			i++;
		while (node->all_cmd[1][++i])
		{
			if (ft_isdigit(node->all_cmd[1][i]) == 0)
			{
				ft_printf(fd, "exit: %s: numeric argument required\n",
					node->all_cmd[1]);
				break ;
			}
		}
	}
	if (data->path != NULL)
	{
		free_split(data->path);
		data->path = NULL;
	}
	exit(g_status);
} */

int	ex_exit(t_data *d, t_parser *node, int fd)
{
	int		i;
	int		j;
	long 	exit_code;

	i = 0;
	j = 0;
	while (node->all_cmd[i] != NULL)
		i++;
	if (i > 2)
	{
		ft_printf(fd, "exit: exit: too many arguments\n");
		g_status = 1;
		return (g_status);
	}
	if (i >= 2)
	{
		while (node->all_cmd[1][j] != '\0')
		{
			if (ft_isdigit(node->all_cmd[1][j]) == 0 &&
				!(node->all_cmd[1][j] == '+' || node->all_cmd[1][j] == '-'))
			{
				ft_printf(fd, "exit exit: %s: numeric argument required\n",
					node->all_cmd[1]);
				g_status = 2;
				return (g_status);
			}
			j++;
		}
		exit_code = ft_atoi(node->all_cmd[1]);
		if (exit_code > 255)
			exit_code = exit_code % 256;
		if (exit_code < 0)
			exit_code += 256;
		g_status = (int)exit_code;
	}
	if (d->path != NULL)
	{
		free_split(d->path);
		d->path = NULL;
	}
	ft_printf(fd, "exit\n");
	exit(g_status);
}
