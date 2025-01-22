/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:58:27 by sebferna          #+#    #+#             */
/*   Updated: 2025/01/22 15:47:32 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	exit2(t_parser *n, int fd)
{
	int		j;
	long	exit_code;

	j = 0;
	if (n->all_cmd[1] != NULL)
	{
		while (n->all_cmd[1][j] != '\0')
		{
			if (ft_isdigit(n->all_cmd[1][j]) == 0 &&
				!(n->all_cmd[1][j] == '+' || n->all_cmd[1][j] == '-'))
			{
				ft_printf (fd, "exit: %s: number required\n", n->all_cmd[1]);
				g_status = 2;
				return (g_status);
			}
			j++;
		}
		exit_code = ft_atoi(n->all_cmd[1]);
		if (exit_code > 255)
			exit_code = exit_code % 256;
		if (exit_code < 0)
			exit_code += 256;
		g_status = (int)exit_code;
	}
	return (g_status);
}

int	ex_exit(t_data *d, t_parser *node, int fd)
{
	int		i;

	i = 0;
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
		g_status = exit2(node, fd);
		if (g_status != 0)
			return (g_status);
	}
	if (d->path != NULL)
	{
		free_split(d->path);
		d->path = NULL;
	}
	ft_printf(fd, "exit\n");
	exit(g_status);
}
