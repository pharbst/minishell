/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 22:13:30 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/11 12:24:27 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	tokenize(char *line, t_token *token, unsigned int i)
{
	t_token			*token;
	unsigned int	dquote;
	unsigned int	squote;
	static int		index;

	dquote = 0;
	squote = 0;
	if (!line)
		return (0);
	while (line[index])
	{
		token_dquote(token, line, &i, &dquote);
		token_squote(token, line, &i, &squote);
		if (!open_quote(token, i))
			token_space(token, &line[index], &i);
		token_escape(token, line, &i);
		token_dollar(token, line, &i);
		token_braket(token, line, &i);
		if (!open_quote(token, i))
			token_redirect(token, line, &i);
		line++;
	}
	return (i);
}

t_pipex	*shell_parsing_main(char *line)
{
	t_pipex			*pipex;
	t_token			*token;
	unsigned int	i;

	if (ft_strlen(line) > 4095)
		return (ft_exit(COMMAND_TOO_LONG), NULL);
	i = 0;
	//trim the line to remove whitespaces
	line = ft_strftrim(line, &ft_isspace);
	if (!line)
		return (NULL);
	token = ft_calloc(2048, sizeof(t_token));
	i = tokenize(line, token, i);
	while (open_quote(token, i))
	{
		line = ft_strjoinfree(ft_strjoinchar(line, '\n'), readline("> "));
		if (ft_strlen(line) > 4095)
			return (ft_exit(COMMAND_TOO_LONG), NULL);
		i = tokenize(line, token, i);
	}
	
	return (pipex);
}
