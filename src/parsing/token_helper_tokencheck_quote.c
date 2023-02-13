/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper_tokencheck_quote.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 09:19:14 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/13 11:20:30 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_dquote(t_token *token, char *line, int *i)
{
	if (*line == '"' && !open_squote(token, *i))
	{
		if (!open_dquote(token, *i))
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

void	token_squote(t_token *token, char *line, int *i)
{
	if (*line == '\'' && !open_dquote(token, *i))
	{
		if (!open_squote(token, *i))
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
	}
}
