/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:33:02 by ccompote          #+#    #+#             */
/*   Updated: 2023/03/26 11:50:59 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_executer.h"

void	free_executor(t_pipex_common *pipex_info)
{
	int	i;

	i = 0;
	ft_free_split(pipex_info->paths);
	while (pipex_info->pipes[i])
	{
		free(pipex_info->pipes[i]);
		i++;
	}
	free(pipex_info->pids);
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

void	waiting(t_pipex_common *pipex_info)
{
	int	i;
	int	error;

	i = 0;
	while (i < pipex_info->number_nodes)
	{
		waitpid(pipex_info->pids[i], &error, 0);
		pipex_info->error_code = WEXITSTATUS(error);
		if (WIFSIGNALED(error) && WTERMSIG(error) == SIGSEGV)
		{
			ft_putstr_fd("Segfault: 11\n", 2);
			pipex_info->error_code = 139;
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
	if (pipex_info->pids[pipex_info->number_nodes - 1] != 5)
		waiting(pipex_info);
}

int	execute(t_shell *shell)
{
	t_pipex			*pipex;
	t_pipex_common	*pipex_info;
	int				i;

	i = 0;
	pipex = shell->p_head;
	pipex_info = ft_calloc(1, sizeof(t_pipex_common));
	if (!pipex_info)
		return (1);
	if (!get_info_for_pipex(pipex_info, pipex, shell->envp))
		return (1);
	while (i < pipex_info->number_nodes)
	{
		piping(pipex, pipex_info, i, shell);
		pipex = pipex->next;
		i++;
	}
	if (shell->p_head->fd_in != 0)
		close(shell->p_head->fd_in);
	finish_piping(pipex_info);
	shell->exit_status = pipex_info->error_code;
	free_executor(pipex_info);
	return (0);
}
