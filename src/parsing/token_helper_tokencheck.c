/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper_tokencheck.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 09:31:46 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/13 13:39:53 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_space(t_token *token, char *line, int *i, int *index)
{
	if (ft_isspace(*line) && !open_quote(token, *i))
	{
		token[*i].type = SPACE;
		token[*i].location = line;
		*i = *i + 1;
		while (ft_isspace(line[*index]))
			*index = *index + 1;
	}
}

void	token_pipe(t_token *token, char *line, int *i)
{
	if (*line == '|' && !open_quote(token, *i))
	{
		token[*i].type = PIPE;
		token[*i].location = line;
		*i = *i + 1;
	}
}

void	token_redirect(t_token *token, char *line, int *i)
{
	if (*line == '>' && !open_quote(token, *i))
	{
		token[*i].type = REDIRECT;
		token[*i].location = line;
		*i = *i + 1;
	}
	else if (*line == '<' && !open_quote(token, *i))
	{
		token[*i].type = REDIRECT;
		token[*i].location = line;
		*i = *i + 1;
	}
}

void	token_dollar(t_token *token, char *line, int *i)
{
	if (*line == '$')
	{
		token[*i].type = DOLLAR;
		token[*i].location = line;
		*i = *i + 1;
	}
}

void	token_braket(t_token *token, char *line, int *i)
{
	if (*line == '[')
	{
		token[*i].type = BRAKET_OPEN;
		token[*i].location = line;
		*i = *i + 1;
	}
	else if (*line == ']')
	{
		token[*i].type = BRAKET_CLOSE;
		token[*i].location = line;
		*i = *i + 1;
	}
}

void	token_escape(t_token *token, char *line, int *i)
{
	if (*line == '\\')
	{
		token[*i].type = ESCAPE;
		token[*i].location = line;
		*i = *i + 1;
	}
}

void	token_string(t_token *token, char *line, int *i)
{
	if (!open_quote(token, *i) && ft_isprint(*line) && !ft_isspace(*line) && !ft_strchr("<>|$\\\"'", *line))
	{
		if (!open_string(token, *i))
		{
			token[*i].type = STRING_OPEN;
			token[*i].location = line;
			*i = *i + 1;
		}
		if (open_string(token, *i) && (ft_isspace(*(line + 1)) || ft_strchr("<>|\"'$", *(line + 1)) || *(line + 1) == '\0'))
		{
			token[*i].type = STRING_CLOSE;
			token[*i].location = line;
			*i = *i + 1;
		}
	}
}
