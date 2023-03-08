/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 21:14:55 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/08 18:03:46 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include <readline/readline.h>
// #include <readline/history.h>
// #include <stdio.h>

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

void	shell_readline(t_shell *shell)
{
	char	*line;

	line = get_prompt_line(shell);
	shell->line = readline(line);
	add_history(shell->line);
	free(line);
}

void	shell_interactive(t_shell *shell)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sa.sa_flags = SA_RESTART;

	while (1)
	{
		sigaction(SIGINT, &sa, NULL);
		shell_readline(shell);
		// shell->line = ft_strdup("cat soemegpn >tmp 2>&1");
		shell->p_head = shell_parsing_main(shell->line, shell->envp);
		print_pipex(shell->p_head);
		if (!ft_strcmp(shell->p_head->cmd, "exit"))
		{
			printf("exit\n");
			break ;
		}
		execute(shell);
		free_pipex(shell->p_head);
	}
	ft_exit(shell);
}

void	shell_alone(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->argv[++i])
		shell->line = strjoinfree(shell->line,
			ft_strjoin(shell->argv[i], " "));
	shell->p_head = shell_parsing_main(shell->line, shell->envp);
	execute(shell);
	ft_exit(shell);
}
