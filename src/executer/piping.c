/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:11:03 by ccompote          #+#    #+#             */
/*   Updated: 2023/03/06 20:18:31 by ccompote         ###   ########.fr       */
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
	if (dup2(p_head->out->fd_left, STDOUT_FILENO) < 0)
		return (0);
	close(p_head->out->fd_left);
	return (1);
}

int	first_process(t_pipex *p_head, t_pipex_common *pipex_info)
{
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
		if (p_head->out)
		{
			if (!handle_outfile(p_head))
				return (0);
		}
		else
		{
			if (dup2(pipex_info->pipes[process - 1][0], STDIN_FILENO) < 0)
				return (0);
			if (dup2(pipex_info->pipes[process][1], STDOUT_FILENO) < 0)
				return (0);
		}
		
	}
	return (1);
}

void builtin(t_pipex *p_head, t_shell *shell, int flag_builtin)
{
	if (flag_builtin == 3)
		bi_echo(get_arraysize(p_head->args), p_head->args);
	else if (flag_builtin == 4)
		print_env(shell->envp);

	else if (flag_builtin == 6)
		pwd();
	// else if (flag_builtin == 7)
	// 	unset(NULL, pipex_info->envp);
}		

int check_builtins(t_pipex *p_head)
{
	if (!ft_strcmp(p_head->cmd, "cd"))
		return (2);
	else if (!ft_strcmp(p_head->cmd, "echo"))
		return (3);
	else if (!ft_strcmp(p_head->cmd, "env"))
		return (4);
	else if (!ft_strcmp(p_head->cmd, "export"))
		return (5);
	else if (!ft_strcmp(p_head->cmd, "pwd"))
		return (6);
	else if (!ft_strcmp(p_head->cmd, "unset"))
		return (7);
	else if (!ft_strcmp(p_head->cmd, "exit"))
		return (8);
	return (0);
}

int check_before_fork(t_pipex *p_head, char *command)
{
	int i;

	i = check_builtins(p_head);
	if (i)
		return (i);
	if (!command)
	{
		printf("%s: command not found\n", p_head->cmd);
		return (0);
	}
	return (1);
}

int open_files(t_pipex *p_head)
{
	if (p_head->in)
	{
		p_head->fd_in = open(p_head->in, O_RDONLY);
		if (p_head->fd_in < 0)
			return (0);
	}
	if (p_head->out)
	{
		if (p_head->out->append)
			p_head->out->fd_left = open(p_head->out->file_right,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			p_head->out->fd_left = open(p_head->out->file_right,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (p_head->out->fd_left < 0)
		return (0);
	}
	return (1);
}

void	piping(t_pipex *p_head, t_pipex_common *pipex_info, int process, t_shell *shell)
{
	pid_t	pid;
	char	*command;
	int flag_builtin;
	
	command = get_cmd(p_head, pipex_info->paths);
	flag_builtin = check_before_fork(p_head, command);
	if (!flag_builtin)
		return ;
	if (flag_builtin == 2 && !p_head->next)
	{
		bi_cd(p_head->args, get_arraysize(p_head->args), shell->envp);
		return ;
	}
	else if (flag_builtin == 5)
	{
		shell->envp = var_export(shell->envp, p_head->args, get_arraysize(p_head->args));
		return ;
	}
	else if (flag_builtin == 7)
	{
		shell->envp = unset( shell->envp, p_head->args);
		return ;
	}

	
	pid = fork();
	if (pid < 0)
		exit(0) ; 
	if (pid == 0)
	{
		if (!open_files(p_head))
			exit(0);
		if (pipex_info->number_nodes > 1)
			close_pipes(pipex_info->pipes, process, pipex_info->number_nodes);
		if (!change_fds_child(p_head, pipex_info, process))
			exit(0) ;
		if (flag_builtin != 1)
		{
			builtin(p_head, shell, flag_builtin);
			exit(0) ;
		}
		execve(command, p_head->args, shell->envp);
	}
}