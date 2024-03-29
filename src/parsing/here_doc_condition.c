/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_condition.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:24:17 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/30 16:42:56 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

bool	hdc_syntax_check(t_parsing *a)
{
	if (a->token[a->token_index].type != STRING_OPEN
		&& a->token[a->token_index].type != DQUOTE_OPEN
		&& a->token[a->token_index].type != SQUOTE_OPEN
		&& a->token[a->token_index].type != DOLLAR)
		return (ft_syntax_error(a), true);
	return (false);
}

char	*get_delimiter(t_parsing *a)
{
	char	*delimiter;
	char	*tmp;

	delimiter = NULL;
	while (a->token[a->token_index].type == STRING_OPEN
		|| a->token[a->token_index].type == DQUOTE_OPEN
		|| a->token[a->token_index].type == SQUOTE_OPEN
		|| a->token[a->token_index].type == DOLLAR)
	{
		if (a->token[a->token_index].type == STRING_OPEN)
			tmp = hdc_string(a);
		else if (a->token[a->token_index].type == DQUOTE_OPEN)
			tmp = hdc_dquote(a);
		else if (a->token[a->token_index].type == SQUOTE_OPEN)
			tmp = hdc_squote(a);
		else if (a->token[a->token_index].type == DOLLAR)
			tmp = hdc_dollar(a);
		delimiter = strjoinfree(delimiter, tmp);
	}
	return (delimiter);
}

void	hdc_child(char *delimiter, int pfd[2])
{
	char	*line;

	line = readline("> ");
	while (ft_strcmp(line, delimiter))
	{
		write(pfd[1], line, ft_strlen(line));
		write(pfd[1], "\n", 1);
		free(line);
		if (isatty(0))
			line = readline("> ");
		else
			line = gnl(0);
	}
	free(line);
	close(pfd[1]);
	exit(0);
}

void	exec_hdc(char *delimiter, int pfd[2], t_parsing *a)
{
	int					pid;
	int					status;
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = SA_RESTART;
	pid = fork();
	if (!pid)
	{
		sigaction(SIGINT, &sa, NULL);
		hdc_child(delimiter, pfd);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (status)
		{
			a->abort = true;
			close(pfd[0]);
		}
		close(pfd[1]);
	}
}

void	hdc(t_parsing *a, t_pipex *pipex)
{
	char	*delimiter;
	int		pfd[2];

	a->token_index += 1;
	if (a->token[a->token_index].type == SPACE_START)
		a->token_index += 1;
	if (hdc_syntax_check(a))
		return ;
	delimiter = get_delimiter(a);
	if (pipe(pfd) == -1)
		return ;
	exec_hdc(delimiter, pfd, a);
	free(delimiter);
	if (!a->abort)
		hdc_interpreter(pfd[0], pipex);
	if (pipex->in)
	{
		free(pipex->in);
		pipex->in = NULL;
	}
}
