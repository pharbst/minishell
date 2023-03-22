/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 15:13:57 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/22 11:22:32 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_prompt_line(t_shell *shell)
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

static bool openquote(char *line)
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

static void	shell_rloq(t_shell_rl rl)
{
	char	*line;

	line = NULL;
	close(rl.pipe_fd[1][0]);
	sigaction(SIGINT, &rl.sa, NULL);
	while (read(rl.pipe_fd[0][0], &rl.buff, 1) > 0)
		line = ft_strjoinchar(line, rl.buff);
	close(rl.pipe_fd[0][0]);
	while (openquote(line))
	{
		if (isatty(STDIN_FILENO))
			rl.tmp = readline("> ");
		else
			rl.tmp = gnl(0);
		if (!rl.tmp)
		{
			ft_putstr_fd("minishell: bash: unexpected EOF while looking for matching `\"'\n", 2);
			free(line);
			close(rl.pipe_fd[1][1]);
			exit(1);
		}
		line = strjoinfree(ft_strjoinchar(line, '\n'), rl.tmp);
	}
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
	// printf("line: %s\n", shell->line);
	free(rl.promt);
	if (!shell->line)
	{
		if (isatty(STDIN_FILENO))
			return (write(1, "exit\n", 5), ft_exit(shell));
		else
			return (ft_exit(shell));
	}
	if (openquote(shell->line))
	{
		if (pipe(rl.pipe_fd[0]) == -1)
			return ;
		if (pipe(rl.pipe_fd[1]) == -1)
			return ;
		write(rl.pipe_fd[0][1], shell->line, ft_strlen(shell->line));
		close(rl.pipe_fd[0][1]);
		free(shell->line);
		shell->line = NULL;
		rl.pid = fork();
		if (!rl.pid)
			shell_rloq(rl);
		else
		{
			close(rl.pipe_fd[0][0]);
			close(rl.pipe_fd[1][1]);
			waitpid(rl.pid, &rl.status, 0);
			if (rl.status)
			{
				if (rl.status == 256)
					ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
				close(rl.pipe_fd[1][0]);
				return ;
			}
			else
			{
				while (read(rl.pipe_fd[1][0], &rl.buff, 1) > 0)
					shell->line = ft_strjoinchar(shell->line, rl.buff);
				close(rl.pipe_fd[1][0]);
			}
		}
	}
	if (ft_strlen(shell->line) > 0)
		add_history(shell->line);
}

