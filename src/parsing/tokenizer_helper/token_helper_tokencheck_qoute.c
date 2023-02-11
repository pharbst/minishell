/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper_tokencheck_1.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 09:19:14 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/11 09:30:57 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_dquote(t_token *token, char *line, unsigned int *i, unsigned int *dquote)
{
	if (*line == '"')
		{
			if (*dquote % 2 == 0)
			{
				token[*i].type = DQOUTE_OPEN;
				token[*i].location = line;
				i++;
			}
			else
			{
				token[*i].type = DQOUTE_CLOSE;
				token[*i].location = line;
				*i++;
			}
			*dquote++;
		}
}

void	token_squote(t_token *token, char *line, unsigned int *i, unsigned int *squote)
{
	if (*line == '\'')
		{
			if (*squote % 2 == 0)
			{
				token[*i].type = SQOUTE_OPEN;
				token[*i].location = line;
				*i++;
			}
			else
			{
				token[*i].type = SQOUTE_CLOSE;
				token[*i].location = line;
				*i++;
			}
			*squote++;
		}
}
