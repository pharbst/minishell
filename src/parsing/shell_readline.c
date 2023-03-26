/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:13:57 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/26 08:01:47 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

char	*get_prompt_line(t_shell *shell)
{
	char	*line;
	char	*pwd;
	char	*tmp;
	char	*usr;

	tmp = getcwd(NULL, 0);
	pwd = last_word(tmp);
	usr = get_var_content(shell->envp, "USER");
	line = ft_strjoinfree(usr, "@minishell ");
	line = ft_strjoinfree(line, pwd);
	line = ft_strjoinfree(line, "$ ");
	free(tmp);
	return (line);
}

bool	openquote(char *line)
{
	int		i;
	bool	s_quote;
	bool	d_quote;

	i = 0;
	s_quote = false;
	d_quote = false;
	while (line[i])
	{
		if (line[i] == '\'' && !d_quote && !s_quote)
			s_quote = true;
		else if (line[i] == '\'' && !d_quote && s_quote)
			s_quote = false;
		if (line[i] == '\"' && !s_quote && !d_quote)
			d_quote = true;
		else if (line[i] == '\"' && !s_quote && d_quote)
			d_quote = false;
		i++;
	}
	if (s_quote || d_quote)
		return (true);
	return (false);
}

void	shell_rliq(t_shell_rl rl, char *line)
{
	while (openquote(line))
	{
		if (isatty(STDIN_FILENO))
			rl.tmp = readline("> ");
		else
			rl.tmp = gnl(0);
		if (!rl.tmp)
		{
			ft_putstrsfd(2, SHELL_NAME, SYNTAX_RL_EOF, NULL);
			free(line);
			close(rl.pipe_fd[1][1]);
			exit(1);
		}
		line = strjoinfree(ft_strjoinchar(line, '\n'), rl.tmp);
	}
}

void	shell_rloq(t_shell_rl rl)
{
	char	*line;

	line = NULL;
	close(rl.pipe_fd[1][0]);
	sigaction(SIGINT, &rl.sa, NULL);
	while (read(rl.pipe_fd[0][0], &rl.buff, 1) > 0)
		line = ft_strjoinchar(line, rl.buff);
	close(rl.pipe_fd[0][0]);
	shell_rliq(rl, line);
	ft_putstr_fd(line, rl.pipe_fd[1][1]);
	free(line);
	close(rl.pipe_fd[1][1]);
	exit(0);
}

void	shell_readline(t_shell *shell)
{
	t_shell_rl	rl;

	ft_bzero(&rl, sizeof(rl));
	rl.sa.sa_handler = SIG_DFL;
	rl.sa.sa_flags = SA_RESTART;
	rl.promt = get_prompt_line(shell);
	if (isatty(STDIN_FILENO))
		shell->line = readline(rl.promt);
	else
	{
		shell->line = gnl(0);
		rl.tmp = shell->line;
		shell->line = ft_strtrim(shell->line, "\n");
		free(rl.tmp);
	}
	free(rl.promt);
	if (!shell->line)
		shell_rl_exit(shell);
	if (openquote(shell->line))
		shell_rl_helper(shell, &rl);
	if (ft_strlen(shell->line) > 0)
		add_history(shell->line);
}
