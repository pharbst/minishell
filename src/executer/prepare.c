/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:14:33 by ccompote          #+#    #+#             */
/*   Updated: 2023/03/03 12:52:10 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_nodes(t_pipex *p_head)
{
	int	i;

	i = 0;
	while (p_head)
	{
		p_head = p_head->next;
		i++;
	}
	return (i);
}

int	get_info_for_pipex(t_pipex_common *pipex_info, t_pipex *p_head, char **envp)
{
	int	i;

	i = 0;
	pipex_info->envp = envp;
	pipex_info->number_nodes = count_nodes(p_head);
	pipex_info->pipes = malloc(sizeof(int *) * pipex_info->number_nodes + 1);
	if (!pipex_info->pipes)
		return (0);
	pipex_info->paths = split_free(get_var_content(envp, "PATH"), ':');
	while (i < pipex_info->number_nodes - 1)
	{
		pipex_info->pipes[i] = malloc(sizeof(int) * 2);
		if (!pipex_info->pipes[i])
			return (0);
		if (pipe(pipex_info->pipes[i]) < 0)
			return (0);
		i++;
	}
	pipex_info->pipes[i] = NULL;
	return (1);
}