/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:27:48 by sebferna          #+#    #+#             */
/*   Updated: 2025/01/08 17:56:09 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_validflag(const char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

void	prints_echo(char **str, int i, int fd)
{
	int	j;

	j = 0;
	while (str[i][j])
	{
		ft_printf(fd, "%c", str[i][j]);
		if (str[i][j] == '\0')
			break ;
		j++;
	}
}

void	echo_print_args(char **str, int i, int fd)
{
	while (str[i])
	{
		prints_echo(str, i, fd);
		if (str[i + 1] || str[i][0] == '\0')
			ft_printf(fd, " ");
		i++;
	}
}

void	ex_echo(char **str, int flag, int fd)
{
	int	i;

	i = 1;
	while (str[i] && is_validflag(str[i]))
	{
		flag = 1;
		i++;
	}
	echo_print_args(str, i, fd);
	if (flag == 0)
		ft_printf(fd, "\n");
	g_status = 0;
}
