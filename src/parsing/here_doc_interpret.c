/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_interpret.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:21:12 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/30 17:43:18 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

char	*hdc_inter_dollar(char *line, int *index, t_shell *shell)
{
	int		start;
	char	*tmp;
	char	*ret;

	(*index)++;
	start = *index;
	while (ft_isalnum(line[*index]))
		(*index)++;
	tmp = ft_substr(line, start, *index - start);
	ret = get_var_content(shell->envp, tmp);
	return (free(tmp), ret);
}

void	hdc_mid(char *line, char **new_line, t_shell *shell)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '$')
			*new_line = strjoinfree(*new_line,
					hdc_inter_dollar(line, &i, shell));
		else
		{
			*new_line = ft_strjoinchar(*new_line, line[i]);
			i++;
		}
	}
}

void	hdc_interpreter(int fd, t_pipex *pipex)
{
	char	*line;
	char	*new_line;
	char	buff[1];
	t_shell	*shell;
	int		pfd[2];

	shell = get_shell(READ, NULL);
	line = NULL;
	new_line = NULL;
	while (read(fd, buff, 1))
		line = ft_strjoinchar(line, buff[0]);
	close(fd);
	hdc_mid(line, &new_line, shell);
	free(line);
	if (pipe(pfd) == -1)
		return ;
	write(pfd[1], new_line, ft_strlen(new_line));
	close(pfd[1]);
	free(new_line);
	pipex->fd_in = pfd[0];
}
