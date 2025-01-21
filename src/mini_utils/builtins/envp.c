/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebferna <sebferna@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:44:28 by sebferna          #+#    #+#             */
/*   Updated: 2025/01/21 17:28:56 by sebferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ex_envp(t_data *data, int fd)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp != NULL)
	{
		if ((tmp->content[1] != '"') && (tmp->content[2] != '"'))
			ft_printf(fd, "%s%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
}

t_envp	*ft_lstlastenv(t_envp *lst)
{
	t_envp	*new;

	new = lst;
	if (lst == 0)
		return (0);
	while (new->next != 0)
		new = new->next;
	return (new);
}

void	lst_addenv_back(t_envp **lst, t_envp *new)
{
	t_envp	*tmp;

	if (*lst != 0)
	{
		tmp = ft_lstlastenv(*lst);
		tmp->next = new;
	}
	else
		*lst = new;
}

void	get_envp(t_data *data, char **envp, int i)
{
	char	**curr;
	t_envp	*tmp;

	while (envp[++i] != NULL)
	{
		tmp = ft_calloc(1, sizeof(t_envp));
		if (!tmp)
			exit (EXIT_FAILURE);
		curr = ft_split(envp[i], '=');
		tmp->name = ft_strdup(curr[0]);
		if (curr[1] == NULL)
			tmp->content = ft_strdup("=");
		else
			tmp->content = ft_strjoin("=", curr[1]);
		tmp->ind = 0;
		tmp->next = NULL;
		lst_addenv_back(&data->envp, tmp);
		free_split(curr);
		curr = NULL;
	}
	set_envp_index(data);
}
