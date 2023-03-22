/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/03/22 11:22:39 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "../../includes/minishell.h"

// static bool openquote(char *line)
// {
// 	int		i;
// 	bool	s_quote;
// 	bool	d_quote;

// 	i = 0;
// 	s_quote = false;
// 	d_quote = false;
// 	while (line[i])
// 	{
// 		if (line[i] == '\'' && !d_quote && !s_quote)
// 			s_quote = true;
// 		else if (line[i] == '\'' && !d_quote && s_quote)
// 			s_quote = false;
// 		if (line[i] == '\"' && !s_quote && !d_quote)
// 			d_quote = true;
// 		else if (line[i] == '\"' && !s_quote && d_quote)
// 			d_quote = false;
// 		i++;
// 	}
// 	if (s_quote || d_quote)
// 		return (true);
// 	return (false);
// }

// void	shell_readline(t_shell *shell)
// {
// 	char	*line;
// 	char	*tmp;

// 	line = get_prompt_line(shell);
// 	shell->line = readline(line);
// 	free(line);
// 	if (!shell->line)
// 		return (write(1, "exit\n", 5), ft_exit(shell));
// 	if (ft_strlen(shell->line) > 0)
// 		add_history(shell->line);
// }

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
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
		shell->line = NULL;
		// print_pipex(shell->p_head);
		if (shell->p_head && !syntax_check(READ, NULL))
		{
			if (shell->p_head->cmd)
				if (!ft_strcmp(shell->p_head->cmd, "exit"))
					break ;
			execute(shell);
			signal_flag(WRITE, false);
		}
		free_pipex(shell);
		shell->p_head = NULL;
	}
	write(1, "exit\n", 5);
	ft_exit(shell);
}

// void	shell_alone(t_shell *shell)
// {
// 	int		i;
// 	char	buff;

// 	i = 0;
// 	while (read(0, &buff, 1) > 0)
// 		shell->line = ft_strjoinchar(shell->line, buff);
// 	shell_parsing_main(shell);
// 	execute(shell);
// 	ft_exit(shell);
// }
