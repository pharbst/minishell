/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:33:02 by ccompote          #+#    #+#             */
/*   Updated: 2023/02/28 18:27:34 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_executor(t_pipex_common *pipex_info)
{
	int	i;

	i = 0;
	ft_free_split(pipex_info->paths);;
	while (pipex_info->pipes[i])
	{
		free(pipex_info->pipes[i]);
		i++;
	}
	free(pipex_info->pipes);
	free(pipex_info);
}

void	close_pipes(int **pipes, int cur, int number_nodes)
{
	int	i;
	int	len;

	len = number_nodes - 1;
	i = 0;
	if (cur == 0)
		close(pipes[0][0]);
	else if (cur == len)
		close(pipes[len - 1][1]);
	else
	{
		close(pipes[cur - 1][1]);
		close(pipes[cur][0]);
	}
	while (pipes[i])
	{
		if (cur < i || cur > i + 1)
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		i++;
	}
}

void	finish_piping(t_pipex_common *pipex_info)
{
	int	i;

	i = 0;
	while (pipex_info->pipes[i])
	{
		close(pipex_info->pipes[i][0]);
		close(pipex_info->pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < pipex_info->number_nodes)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}

int	execute(t_pipex *p_head, char **envp)
{
	t_pipex_common	*pipex_info;
	int				i;

	pipex_info = malloc(sizeof(t_pipex_common));
	if (!pipex_info)
		return (0);
	if (!get_info_for_pipex(pipex_info, p_head, envp))
		return (0);
	i = 0;
	while (i < pipex_info->number_nodes)
	{
		piping(p_head, pipex_info, i);
		p_head = p_head->next;
		i++;
	}
	finish_piping(pipex_info);
	free_executor(pipex_info);
	return (1);
}
