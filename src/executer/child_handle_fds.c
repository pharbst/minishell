/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_handle_fds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:22:34 by ccompote          #+#    #+#             */
/*   Updated: 2023/03/23 17:14:24 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

// ctrl-c - sosatb
// ctrl-\ - sosatb
// ctrl-d - sosatb

// ls >| llllogs
// ls > llllogs

// exit takes only numeric arguments and exits with correct exitcode

//close all files?

//echo $b (not exist)
//ERROR: malloc failed in str_cat
///bin/echo $notexist - frees not allocated and exits

// /bin/echo $HOME - trash in first arg
// /Users/ccompote
// arg[0]: ???
// arg[1]: /Users/ccompote

//  /bin/ls
//  pointer of arg[0] being freed was not allocated

// < tmp 
//finishes before executor

// echo '$USER' must print $USER



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
