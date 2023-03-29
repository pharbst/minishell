/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_readline_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 03:46:43 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/29 15:57:51 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

void	shell_rloq_parent(t_shell *shell, t_shell_rl *rl)
{
	close(rl->pipe_fd[0][0]);
	close(rl->pipe_fd[1][1]);
	waitpid(rl->pid, &rl->status, 0);
	if (rl->status)
	{
		if (rl->status == 256)
			ft_putstrsfd(2, SHELL_NAME, SYNTAX_EOF, NULL);
		close(rl->pipe_fd[1][0]);
		return ;
	}
	else
	{
		while (read(rl->pipe_fd[1][0], &rl->buff, 1) > 0)
			shell->line = ft_strjoinchar(shell->line, rl->buff);
		close(rl->pipe_fd[1][0]);
	}
}

void	shell_rl_helper(t_shell *shell, t_shell_rl *rl)
{
	if (pipe(rl->pipe_fd[0]) == -1)
		return ;
	if (pipe(rl->pipe_fd[1]) == -1)
		return ;
	write(rl->pipe_fd[0][1], shell->line, ft_strlen(shell->line));
	close(rl->pipe_fd[0][1]);
	free(shell->line);
	shell->line = NULL;
	rl->pid = fork();
	if (!rl->pid)
		shell_rloq(*rl);
	else
		shell_rloq_parent(shell, rl);
}

void	shell_rl_exit(t_shell *shell)
{
	if (!isatty(STDIN_FILENO))
		ft_exit(-1, NULL, shell);
	ft_exit(1, NULL, shell);
}
