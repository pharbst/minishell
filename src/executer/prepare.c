/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:14:33 by ccompote          #+#    #+#             */
/*   Updated: 2023/02/28 17:15:02 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**find_path(char **envp)
{
	int		i;
	char	**res;

	i = 0;
	res = NULL;
	while (envp[i])
	{
		if (!ft_strncmp("PATH", envp[i], 4))
		{
			res = ft_split(&envp[i][5], ':');
			if (!res)
				return (NULL);
			break ;
		}
		i++;
	}
	if (!envp[i])
		return (NULL);
	return (res);
}

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
	pipex_info->paths = find_path(pipex_info->envp);
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