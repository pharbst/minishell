/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 21:14:55 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/18 12:21:51 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	shell_readline(t_shell *shell)
{
	char	*line;

	line = get_prompt_line(shell);
	shell->line = readline(line);
	if (!shell->line)
		return (write(1, "exit\n", 5), ft_exit(shell));
	if (ft_strlen(shell->line) > 0)
		add_history(shell->line);
	free(line);
}

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (signal_flag(READ, false))
			write(1, "\n", 1);
		else
		{
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			shell_readline(get_shell(READ, NULL));
		}
	}
}

void	shell_interactive(t_shell *shell)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &sigint_handler;
	sa.sa_flags = SA_RESTART;

	while (1)
	{
		sigaction(SIGINT, &sa, NULL);
		shell_readline(shell);
		syntax_check(WRITE, false);
		shell_parsing_main(shell);
		print_pipex(shell->p_head);
		if (shell->p_head && !syntax_check(READ, NULL))
		{
			if (shell->p_head->cmd)
				if (!ft_strcmp(shell->p_head->cmd, "exit"))
					break ;
			execute(shell);
			signal_flag(WRITE, false);
		}
		free_pipex(shell);
	}
	write(1, "exit\n", 5);
	ft_exit(shell);
}

void	shell_alone(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->argv[++i])
		shell->line = strjoinfree(shell->line,
			ft_strjoin(shell->argv[i], " "));
	shell_parsing_main(shell);
	execute(shell);
	ft_exit(shell);
}
