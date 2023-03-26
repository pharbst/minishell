/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 00:00:00 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/26 09:25:47 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_structs.h"
#include "minishell_parsing.h"
#include "minishell_buildins.h"
#include "minishell_executer.h"


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

void	pre_execute(t_shell *shell)
{
	if (shell->p_head->cmd)
	{
		if (!ft_strcmp(shell->p_head->cmd, "exit"))
		{
			ft_exit(get_arraysize(shell->p_head->args),
				shell->p_head->args, shell);
		// 	if (get_arraysize(shell->p_head->args) > 1)
		// 	{
		// 		if (!ft_atoi(shell->p_head->args[1]) && *shell->p_head->args[1] != '0')
		// 		{
		// 			shell->exit_status = 255;
		// 			write(1, "exit\n", 5);
		// 			ft_putstrsfd(2, "exit: ", shell->p_head->args[1], EXIT_WRONG_ARG, NULL);
		// 			ft_exit(shell);
		// 		}
		// 	}
		// 	if (get_arraysize(shell->p_head->args) > 2)
		// 	{
		// 		shell->exit_status = 1;
		// 		ft_putstr_fd(EXIT_TOO_MANY_ARGS, 2);
		// 	}
		// 	else
		// 		ft_exit(shell);
		}
	}
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
		sigaction(SIGINT, &sa, NULL);
		shell_readline(shell);
		syntax_check(WRITE, false);
		shell_parsing_main(shell);
		shell->line = NULL;
		// print_pipex(shell->p_head);
		if (shell->p_head && !syntax_check(READ, NULL))
			pre_execute(shell);
		free_pipex(shell);
		shell->p_head = NULL;
	}
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
