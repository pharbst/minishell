/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_dup_open.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:34:45 by ccompote          #+#    #+#             */
/*   Updated: 2023/03/28 21:35:07 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_executer.h"

int	change_fds_child(t_pipex *p_head, t_pipex_common *pipex_info, int process)
{
	if (process == 0)
	{
		if (!first_process(p_head, pipex_info))
			return (0);
	}
	else if (process == pipex_info->number_nodes - 1)
	{
		if (!last_process(p_head, pipex_info, process))
			return (0);
	}
	else
	{
		if (!middle_process(p_head, pipex_info, process))
			return (0);
	}
	return (1);
}

int	open_outfile(t_pipex *p_head)
{
	t_redir_out	*tmp;

	tmp = p_head->out;
	while (tmp)
	{
		if (*tmp->file_right != '&')
		{
			if (tmp->append)
				tmp->fd_right = open(tmp->file_right,
						O_CREAT | O_WRONLY | O_APPEND, 0644);
			else
				tmp->fd_right = open(tmp->file_right,
						O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (tmp->fd_right < 0)
				return (ft_putstrsfd(2, tmp->file_right, NO_PERM, NULL), 0);
		}
		else if (*tmp->file_right == '&')
		{
			tmp->fd_right = ft_atoi(tmp->file_right + 1);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	open_files(t_pipex *p_head)
{
	if (p_head->in)
	{
		p_head->fd_in = open(p_head->in, O_RDONLY);
		if (p_head->fd_in < 0)
			return (ft_putstrsfd(2, p_head->in, NO_SUCH_FILE, NULL), 0);
	}
	if (p_head->out)
		return (open_outfile(p_head));
	return (1);
}
