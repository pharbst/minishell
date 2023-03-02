/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:11:03 by ccompote          #+#    #+#             */
/*   Updated: 2023/03/01 17:14:39 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd(t_pipex *p_head, char **paths)
{
	int		i;
	char	*tmp;
	char	*command;

	i = 0;
	if (!access(p_head->cmd, 0))
		return (p_head->cmd);
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

int	handle_outfile(t_pipex *p_head)
{
	if (p_head->out->append)
		p_head->out->fd_left = open(p_head->out->file_right,
			O_CREAT | O_WRONLY | O_APPEND, 0644);			
	else
		p_head->out->fd_left = open(p_head->out->file_right,
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (p_head->out->fd_left < 0)
		return (0);
	if (dup2(p_head->out->fd_left, STDOUT_FILENO) < 0)
		return (0);
	close(p_head->out->fd_left);
	return (1);
}

int	first_process(t_pipex *p_head, t_pipex_common *pipex_info)
{
	if (p_head->fd_in)
	{
		dup2(p_head->fd_in, STDIN_FILENO);
		close(p_head->fd_in);
	}
	else if (p_head->in)
	{
		p_head->fd_in = open(p_head->in, O_RDONLY);
		if (p_head->fd_in < 0)
			return (0);
		if (dup2(p_head->fd_in, STDIN_FILENO) < 0)
			return (0);
		close(p_head->fd_in);
	}
	if (p_head->next)
	{
		if (dup2(pipex_info->pipes[0][1], STDOUT_FILENO) < 0)
			return (0);
	}
	else
	{
		if (p_head->out)
		{
			if (!handle_outfile(p_head))
				return (0);
		}
	}
	return (1);
}

int	change_fds_child(t_pipex *p_head, t_pipex_common *pipex_info, int process)
{
	if (process == 0)
	{
		if (!first_process(p_head, pipex_info))
			return (0);
	}
	else if (process == pipex_info->number_nodes - 1)
	{
		if (p_head->out)
		{
			if (!handle_outfile(p_head))
				return (0);
		}
		if (dup2(pipex_info->pipes[process - 1][0], STDIN_FILENO) < 0)
			return (0);
	}
	else
	{
		if (dup2(pipex_info->pipes[process - 1][0], STDIN_FILENO) < 0)
			return (0);
		if (dup2(pipex_info->pipes[process][1], STDOUT_FILENO) < 0)
			return (0);
	}
	return (1);
}

void	piping(t_pipex *p_head, t_pipex_common *pipex_info, int process)
{
	pid_t	pid;
	char	*command;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		if (pipex_info->number_nodes > 1)
			close_pipes(pipex_info->pipes, process, pipex_info->number_nodes);
		if (!change_fds_child(p_head, pipex_info, process))
			return ;
		command = get_cmd(p_head, pipex_info->paths);
		execve(command, p_head->args, pipex_info->envp);
	}
}