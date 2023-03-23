/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:14:33 by ccompote          #+#    #+#             */
/*   Updated: 2023/03/23 09:40:23 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_nodes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex)
	{
		pipex = pipex->next;
		i++;
	}
	return (i);
}

int	get_info_for_pipex(t_pipex_common *pipex_info, t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	pipex_info->number_nodes = count_nodes(pipex);
	pipex_info->pids = ft_calloc(pipex_info->number_nodes, sizeof(pid_t));
	pipex_info->pipes = ft_calloc(pipex_info->number_nodes + 1, sizeof(int *));
	if (!pipex_info->pipes)
		return (0);
	pipex_info->paths = split_free(get_var_content(envp, "PATH"), ':');
	if (!pipex_info->paths)
	{
		printf("%s: No such file or directory\n", pipex->cmd);
		return (0);
	}
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
