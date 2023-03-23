/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper_tokencheck.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 09:31:46 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/23 09:48:03 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	token_space(t_token *token, int *i, char *line, int *index)
{
	if (ft_isspace(line[*index]) && !open_quote(token, *i))
	{
		token[*i].type = SPACE_START;
		token[*i].index = *index;
		*i += 1;
		while (ft_isspace(line[*index]))
			*index += 1;
		*index -= 1;
	}
}

void	token_pipe(t_token *token, int *i, char *line, int index)
{
	if (line[index] == '|' && !open_quote(token, *i))
	{
		token[*i].type = PIPE;
		token[*i].index = index;
		*i = *i + 1;
	}
}

void	token_redirect(t_token *token, int *i, char *line, int index)
{
	if (line[index] == '>' && !open_quote(token, *i))
	{
		token[*i].type = REDIRECT_OUT;
		token[*i].index = index;
		*i = *i + 1;
	}
	else if (line[index] == '<' && !open_quote(token, *i))
	{
		token[*i].type = REDIRECT_IN;
		token[*i].index = index;
		*i = *i + 1;
	}
}

void	token_dollar(t_token *token, int *i, char *line, int index)
{
	if (line[index] == '$')
	{
		token[*i].type = DOLLAR;
		token[*i].index = index;
		*i = *i + 1;
	}
}

void	token_string(t_token *token, int *i, char *line, int index)
{
	if (!open_quote(token, *i) && ft_isprint(line[index])
		&& !ft_isspace(line[index]) && !ft_strchr("<>|$\"'", line[index]))
	{
		if (!open_string(token, *i))
		{
			token[*i].type = STRING_OPEN;
			token[*i].index = index;
			*i = *i + 1;
		}
		if (open_string(token, *i) && (ft_isspace(line[index + 1])
				|| ft_strchr("<>|\"'$", line[index + 1])
				|| line[index + 1] == '\0'))
		{
			token[*i].type = STRING_CLOSE;
			token[*i].index = index;
			*i = *i + 1;
		}
	}
}
