/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_condition.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:24:17 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/01 16:33:53 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hdc(t_parsing *a, t_pipex *pipex)
{
	char	*delimiter;
	int		pfd[2];
	char	*line;

	a->token_index += 1;
	if (a->token[a->token_index].type == SPACE_START)
		a->token_index += 1;
	delimiter = str_cat(a);
	if (pipe(pfd) == -1)
	{
		printf("minishell: pipe error\n");
		return ;
	}
	line = readline("> ");
	while (ft_strcmp(line, delimiter))
	{
		write(pfd[1], line, ft_strlen(line));
		write(pfd[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(pfd[1]);
	pipex->fd_in = pfd[0];
	if (pipex->in)
	{
		free(pipex->in);
		pipex->in = NULL;
	}
}
