/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper_tokencheck.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 09:31:46 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/11 09:39:48 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_space(t_token *token, char **line, unsigned int *i)
{
	if (ft_isspace(**line))
	{
		token[*i].type = SPACE;
		token[*i].location = *line;
		*i++;
		while (ft_isspace(**line))
			*line++;
	}
}

void	token_pipe(t_token *token, char **line, unsigned int *i)
{
	if (**line == '|')
	{
		token[*i].type = PIPE;
		token[*i].location = *line;
		*i++;
		*line++;
	}
}

void	token_redirect(t_token *token, char **line, unsigned int *i)
{
	if (**line == '>')
	{
		token[*i].type = REDIRECT;
		token[*i].location = *line;
		*i++;
		*line++;
	}
	else if (**line == '<')
	{
		token[*i].type = REDIRECT;
		token[*i].location = *line;
		*i++;
		*line++;
	}
}

void	token_dollar(t_token *token, char **line, unsigned int *i)
{
	if (**line == '$')
	{
		token[*i].type = DOLLAR;
		token[*i].location = *line;
		*i++;
		*line++;
	}
}

void	token_braket(t_token *token, char **line, unsigned int *i)
{
	if (**line == '[')
	{
		token[*i].type = BRAKET_OPEN;
		token[*i].location = *line;
		*i++;
		*line++;
	}
	else if (**line == ']')
	{
		token[*i].type = BRAKET_CLOSE;
		token[*i].location = *line;
		*i++;
		*line++;
	}
}
