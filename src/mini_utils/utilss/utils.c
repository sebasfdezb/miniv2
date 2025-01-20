/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:43:24 by sebferna          #+#    #+#             */
/*   Updated: 2025/01/20 16:07:19 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	draw(void)
{
	printf(" ███████╗██████╗  \n");
	printf(" ██╔════╝██╔══██╗ \n");
	printf(" █████╗  ██████╔╝ \n");
	printf(" ██╔══╝  ██╔═══╝  \n");
	printf(" ███████╗██║      \n");
	printf(" ╚══════╝╚═╝      \n");
	printf("\n");
}

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

int	is_valid_identifier(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (!((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z')
			|| str[0] == '_'))
		return (0);
	while (str[i])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A'
					&& str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9')
				|| str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}


void	export_content(t_data *data, char *str, char **aux, t_envp *tmp)
{
	t_envp	*new;

	if (!is_valid_identifier(str))
	{
		ft_printf(2, "Error\n");
		g_status = 1;
		return ;
	}
	aux = ft_split(str, '=');
	if (!aux)
		return ;
	if (check_node(data, aux) == EXIT_SUCCESS)
	{
		free_split(aux);
		return ;
	}
	new = malloc(sizeof(t_envp));
	if (!new)
		return ;
	new->name = ft_strdup(aux[0]);
	if (aux[1] == NULL)
		new->content = ft_strdup("\"\"");
	else if (aux[1])
		new->content = ft_strjoin("=", aux[1]);
	new->ind = 0;
	tmp = data->envp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
	free_split(aux);
}
