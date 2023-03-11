/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_handle_fds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:22:34 by ccompote          #+#    #+#             */
/*   Updated: 2023/03/11 04:40:20 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_outfile(t_pipex *p_head)
{
	t_redir_out	*tmp;

	tmp = p_head->out;
	while (tmp)
	{
		printf("dup2: %d --> %d\n", tmp->fd_right, tmp->fd_left);
		fflush(stdout);
		if (dup2(tmp->fd_right, tmp->fd_left) < 0)
			return (printf("debug return 0 cause dup2 is less than 0\n"), fflush(stdout), 0);
		printf("fd_right: %d\n", tmp->fd_right);
		fflush(stdout);
		if (tmp->fd_right > 2)
		{
			printf("close: %d\n", tmp->fd_right);
			close(tmp->fd_right);
		}
		tmp = tmp->next;
	}
	return (1);
}

// ctrl-c - sosatb
// ctrl-\ - sosatb
// ctrl-d - sosatb

// ls >| llllogs
// ls > llllogs

// exit takes only numeric arguments and exits with correct exitcode
//при выполнении команд всегда обращаемся к внутреннему, при команде экспорт обновляются оба
//a=b without echo (2 envs)
//bash-3.2$ export =ab
// bash: export: `=ab': not a valid identifier
//close all files?

int first_process(t_pipex *p_head, t_pipex_common *pipex_info)
{
	if (p_head->next)
	{
		if (dup2(pipex_info->pipes[0][1], STDOUT_FILENO) < 0)
			return (0);
	}
	if (p_head->fd_in)
	{
		if (dup2(p_head->fd_in, STDIN_FILENO) < 0)
			return (0);
		close(p_head->fd_in);
	}
	else if (p_head->in)
	{
		if (dup2(p_head->fd_in, STDIN_FILENO) < 0)
			return (0);
		close(p_head->fd_in);
	}
	if (p_head->out)
	{
		printf("out\n");
		if (!handle_outfile(p_head))
			return (0);
	}
	return (1);
}

int middle_process(t_pipex *p_head, t_pipex_common *pipex_info, int process)
{
	if (dup2(pipex_info->pipes[process - 1][0], STDIN_FILENO) < 0)
		return (0);
	if (dup2(pipex_info->pipes[process][1], STDOUT_FILENO) < 0)
		return (0);
	if (p_head->fd_in)
	{
		if (dup2(p_head->fd_in, STDIN_FILENO) < 0)
			return (0);
		close(p_head->fd_in);
	}
	if (p_head->out)
	{
		if (!handle_outfile(p_head))
			return (0);
	}
	return (1);
}

int last_process(t_pipex *p_head, t_pipex_common *pipex_info, int process)
{
	if (p_head->fd_in)
	{
		if (dup2(p_head->fd_in, STDIN_FILENO) < 0)
			return (0);
		close(p_head->fd_in);
	}
	else
	{
		if (dup2(pipex_info->pipes[process - 1][0], STDIN_FILENO) < 0)
			return (0);
	}
	if (p_head->out)
	{
		if (!handle_outfile(p_head))
			return (0);
	}
	return (1);
}