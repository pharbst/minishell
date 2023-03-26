/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:11:03 by ccompote          #+#    #+#             */
/*   Updated: 2023/03/26 22:03:05 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_executer.h"

char	*get_cmd(t_pipex *p_head, char **paths)
{
	int		i;
	char	*tmp;
	char	*command;

	i = 0;
	if (!p_head->cmd)
		return (NULL);
	if (ft_strchr("/.", *p_head->cmd))
	{
		if (!access(p_head->cmd, 0))
			return (p_head->cmd);
	}
	if (paths)
	{
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
	}
	return (NULL);
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

int open_files(t_pipex *p_head)
{
	t_redir_out	*tmp;

	if (p_head->in)
	{
		p_head->fd_in = open(p_head->in, O_RDONLY);
		if (p_head->fd_in < 0)
			return (ft_putstrsfd(2, p_head->in, NO_SUCH_FILE, NULL), 0);
	}
	if (p_head->out)
	{
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
	}
	return (1);
}

void	piping(t_pipex *p_head, t_pipex_common *pipex_info, int process, t_shell *shell)
{
	char	*command;
	int flag_builtin;
	struct sigaction sa;
	int status;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = SA_RESTART;

	
	command = get_cmd(p_head, pipex_info->paths);
	flag_builtin = check_before_fork(p_head, command);
	if (!flag_builtin)
	{
		pipex_info->pids[pipex_info->number_nodes - 1] = 5;
		pipex_info->error_code = 127;
		return (free(command));
	}
	status = builtin_main(p_head, shell, flag_builtin);
	if (status != 2)
	{
		pipex_info->pids[pipex_info->number_nodes - 1] = 5;
		pipex_info->error_code = status;
		return (free(command));
	}
	// flag_builtin = check_before_fork(p_head);
	if (!flag_builtin)
	{
		pipex_info->pids[pipex_info->number_nodes - 1] = 5;
		pipex_info->error_code = 127;
		return (free(command));
	}
	// status = builtin_main(p_head, shell, flag_builtin);
	// printf("%d\n", status);
	// if (status != 2)
	// {
	// 	pipex_info->pids[pipex_info->number_nodes - 1] = 5;
	// 	pipex_info->error_code = status;
	// 	// return (free(command));
	// 	// return ;
	// }
	signal_flag(WRITE, true);
	pipex_info->pids[process] = fork();
	if (pipex_info->pids[process] < 0)
		exit(1); 
	if (pipex_info->pids[process] == 0)
	{
		// pipex_info->paths = split_free(get_var_content(shell->envp, "PATH"), ':');
		// if (!pipex_info->paths)
		// {
		// 	if (flag_builtin == 1 || flag_builtin == 4)
		// 	{
		// 		ft_putstrsfd(2, p_head->cmd, NO_SUCH_FILE, NULL);
		// 		exit (1);
		// 	}
		// }
		// command = get_cmd(p_head, pipex_info->paths);
		// if (!command && flag_builtin == 1)
		// {
		// 	ft_putstrsfd(2, p_head->cmd, NO_COMMAND, NULL);
		// 	exit(127);
		// }
		sigaction(SIGINT, &sa, NULL);
		if (!open_files(p_head))
			exit(1);
		if (pipex_info->number_nodes > 1)
			close_pipes(pipex_info->pipes, process, pipex_info->number_nodes);
		if (!change_fds_child(p_head, pipex_info, process))
			exit(1);
		if (flag_builtin != 1)
			exit(builtin_child(p_head, shell, flag_builtin));
		if (command)
			execve(command, p_head->args, shell->envp);
		else
			exit (0);
	}
}
