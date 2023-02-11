/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 22:13:30 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/11 12:58:58 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	tokenize(char *line, t_token *token, unsigned int i)
{
	unsigned int	dquote;
	unsigned int	squote;
	static int		index;

	dquote = 0;
	squote = 0;
	if (!line)
		return (0);
	while (line[index])
	{
		if (!open_squote(token, i))
			token_dquote(token, &line[index], &i, &dquote);
		if (!open_dquote(token, i))
			token_squote(token, &line[index], &i, &squote);
		if (!open_quote(token, i))
			token_space(token, &line[index], &i, &index);
		token_escape(token, &line[index], &i);
		token_dollar(token, &line[index], &i);
		token_braket(token, &line[index], &i);
		if (!open_quote(token, i))
			token_redirect(token, &line[index], &i);
		line++;
	}
	return (i);
}

t_pipex	*shell_parsing_main(char *line)
{
	t_pipex			*pipex;
	t_token			*token;
	unsigned int	i;

	pipex = NULL;
	if (ft_strlen(line) > 4095)
		return (NULL);
	i = 0;
	line = ft_strftrim(line, &ft_isspace);
	if (!line)
		return (NULL);
	token = ft_calloc(2048, sizeof(t_token));
	i = tokenize(line, token, i);
	while (open_quote(token, i))
	{
		line = ft_strjoinfree(ft_strjoinchar(line, '\n'), readline("> "));
		if (ft_strlen(line) > 4095)
			return (NULL);
		i = tokenize(line, token, i);
	}
	
	return (pipex);
}
