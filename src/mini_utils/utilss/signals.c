/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:04:12 by sebferna          #+#    #+#             */
/*   Updated: 2025/01/22 16:05:10 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sig_ctrlslash(int sig)
{
	if (sig == SIGQUIT)
	{
		printf("Quit: 3\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	sig_ctrlc(int sig)
{
	if (sig == SIGINT)
	{
		printf("\033[K\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	signals(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		printf("\033[K\n");
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
	}
}
