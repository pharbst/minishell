/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_handle_fds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:22:34 by ccompote          #+#    #+#             */
/*   Updated: 2023/03/28 20:05:58 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_executer.h"

int	handle_outfile(t_pipex *p_head)
{
	t_redir_out	*tmp;

	tmp = p_head->out;
	while (tmp)
	{
		if (dup2(tmp->fd_right, tmp->fd_left) < 0)
			return (0);
		if (tmp->fd_right > 2)
			close(tmp->fd_right);
		tmp = tmp->next;
	}
	return (1);
}

int	first_process(t_pipex *p_head, t_pipex_common *pipex_info)
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
		if (!handle_outfile(p_head))
			return (0);
	}
	return (1);
}

int	middle_process(t_pipex *p_head, t_pipex_common *pipex_info, int process)
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

int	last_process(t_pipex *p_head, t_pipex_common *pipex_info, int process)
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
