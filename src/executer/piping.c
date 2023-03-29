/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:11:03 by ccompote          #+#    #+#             */
/*   Updated: 2023/03/29 18:00:42 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_executer.h"

int	exec_built_before_fork(t_pipex_common *pipex_info,
	t_pipex *p_head, t_shell *shell)
{
	int	status;

	pipex_info->flag_builtin = check_before_fork(p_head);
	if (!pipex_info->flag_builtin)
	{
		pipex_info->pids[pipex_info->number_nodes - 1] = 5;
		pipex_info->error_code = 127;
		return (1);
	}
	status = builtin_main(p_head, shell, pipex_info->flag_builtin);
	if (status != 2)
	{
		pipex_info->pids[pipex_info->number_nodes - 1] = 5;
		pipex_info->error_code = status;
		return (1);
	}
	return (0);
}

void	child_paths(t_pipex *p_head, t_pipex_common *pipex_info, t_shell *shell)
{
	pipex_info->paths = split_free(get_var_content(shell->envp, "PATH"), ':');
	if (!pipex_info->paths)
	{
		if (pipex_info->flag_builtin == 1 || pipex_info->flag_builtin == 4)
		{
			ft_putstrsfd(2, p_head->cmd, NO_SUCH_FILE, NULL);
			exit (1);
		}
	}
}

void	exec_child(t_pipex *p_head, t_pipex_common *pipex_info,
	int process, t_shell *shell)
{
	char	*command;

	if (!open_files(p_head))
		exit(1);
	if (pipex_info->number_nodes > 1)
		close_pipes(pipex_info->pipes, process, pipex_info->number_nodes);
	if (!change_fds_child(p_head, pipex_info, process))
		exit(1);
	if (pipex_info->flag_builtin != 1)
		exit(builtin_child(p_head, shell, pipex_info->flag_builtin));
	child_paths(p_head, pipex_info, shell);
	command = get_cmd(p_head, pipex_info->paths);
	if (!command && pipex_info->flag_builtin == 1)
	{
		ft_putstrsfd(2, p_head->cmd, NO_COMMAND, NULL);
		exit(127);
	}
	if (command)
		execve(command, p_head->args, shell->envp);
	else
		exit (0);
}

void	piping(t_pipex *p_head, t_pipex_common *pipex_info,
	int process, t_shell *shell)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = SA_RESTART;
	if (exec_built_before_fork(pipex_info, p_head, shell))
		return ;
	signal_flag(WRITE, true);
	pipex_info->pids[process] = fork();
	if (pipex_info->pids[process] < 0)
		exit(1);
	if (pipex_info->pids[process] == 0)
	{
		sigaction(SIGINT, &sa, NULL);
		signal(SIGQUIT, SIG_DFL);
		exec_child(p_head, pipex_info, process, shell);
	}
}
