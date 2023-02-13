/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper_tokencheck_quote.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 09:19:14 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/13 05:44:54 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_dquote(t_token *token, char *line, int *i)
{
	if (*line == '"')
	{
		if (!open_dquote(token, i))
		{
			token[*i].type = DQUOTE_OPEN;
			token[*i].location = line;
			*i = *i + 1;
		}
		else
		{
			token[*i].type = DQUOTE_CLOSE;
			token[*i].location = line;
			*i = *i + 1;
		}
	}
}

void	token_squote(t_token *token, char *line, unsigned int *i, unsigned int *squote)
{
	if (*line == '\'')
	{
		if (*squote % 2 == 0)
		{
			token[*i].type = SQUOTE_OPEN;
			token[*i].location = line;
			*i = *i + 1;
		}
		else
		{
			token[*i].type = SQUOTE_CLOSE;
			token[*i].location = line;
			*i = *i + 1;
		}
		*squote = *squote + 1;
	}
}
