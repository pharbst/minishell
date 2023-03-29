/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 00:00:00 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/29 19:07:25 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_structs.h"
#include "minishell_parsing.h"
#include "minishell_buildins.h"
#include "minishell_executer.h"

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (signal_flag(READ, false))
		{
			write(1, "\n", 1);
		}
		else
		{
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	pre_execute(t_shell *shell)
{
	int	skip_exec;

	skip_exec = 0;
	if (shell->p_head->cmd)
	{
		if (!ft_strcmp(shell->p_head->cmd, "exit"))
		{
			skip_exec = ft_exit(get_arraysize(shell->p_head->args),
					shell->p_head->args, shell);
		}
	}
	if (!skip_exec)
		execute(shell);
	signal_flag(WRITE, false);
}

void	shell_interactive(t_shell *shell)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &sigint_handler;
	sa.sa_flags = SA_RESTART;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		sigaction(SIGINT, &sa, NULL);
		signal_flag(WRITE, false);
		shell_readline(shell);
		syntax_check(WRITE, false);
		signal_flag(WRITE, true);
		shell_parsing_main(shell);
		// print_pipex(shell->p_head);
		shell->line = NULL;
		if (shell->p_head && !syntax_check(READ, NULL))
			pre_execute(shell);
		free_pipex(shell);
		shell->p_head = NULL;
	}
}
