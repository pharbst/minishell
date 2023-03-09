/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:33:02 by ccompote          #+#    #+#             */
/*   Updated: 2023/03/09 23:27:40 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void waiting(t_pipex_common *pipex_info)
{
	int i;

	i = 0;
	while (i < pipex_info->number_nodes)
	{
		waitpid(pipex_info->pids[i], NULL, 0);
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
	waiting(pipex_info);
}

int	execute(t_shell *shell)
{
	t_pipex *pipex;
	t_pipex_common	*pipex_info;
	int				i;
	int j;

	j = 0;
	i = 0;
	pipex = shell->p_head;
	pipex_info = malloc(sizeof(t_pipex_common));
	if (!pipex_info)
		return (0);
	
	if (!get_info_for_pipex(pipex_info, pipex, shell->envp))
		return (0);
	while (i < pipex_info->number_nodes)
	{
		piping(pipex, pipex_info, i, shell);
		pipex = pipex->next;
		i++;
	}
	finish_piping(pipex_info);
	free_executor(pipex_info);
	return (1);
}
