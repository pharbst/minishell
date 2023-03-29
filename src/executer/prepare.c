/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:14:33 by ccompote          #+#    #+#             */
/*   Updated: 2023/03/29 19:06:47 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_executer.h"

char	*get_cmd_relative(char **paths, t_pipex *p_head)
{
	char	*tmp;
	char	*command;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		command = ft_strjoin(tmp, p_head->cmd);
		if (!command)
			return (NULL);
		free(tmp);
		if (!access(command, 0))
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

char	*get_cmd(t_pipex *p_head, char **paths)
{
	int	i;

	i = 0;
	if (!p_head->cmd)
		return (NULL);
	if (ft_strchr("/.", *p_head->cmd))
	{
		while (p_head->cmd[i] && !ft_isalnum(p_head->cmd[i]))
			i++;
		if (!p_head->cmd[i])
			return (NULL);
		if (!access(p_head->cmd, 0))
			return (p_head->cmd);
	}
	else if (paths)
		return (get_cmd_relative(paths, p_head));
	return (NULL);
}

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
	(void)envp;
	pipex_info->number_nodes = count_nodes(pipex);
	pipex_info->pids = ft_calloc(pipex_info->number_nodes, sizeof(pid_t));
	pipex_info->pipes = ft_calloc(pipex_info->number_nodes + 1, sizeof(int *));
	if (!pipex_info->pipes)
		return (0);
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
