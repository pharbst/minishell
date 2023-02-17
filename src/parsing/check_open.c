/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_open.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 12:14:56 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/17 14:24:08 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	open_quote(t_token *token, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		if (token[j].type == DQUOTE_OPEN)
			while (token[j].type != DQUOTE_CLOSE)
				if (j++ == i)
					return (true);
		if (token[j].type == SQUOTE_OPEN)
			while (token[j].type != SQUOTE_CLOSE)
				if (j++ == i)
					return (true);
		j++;
	}
	return (false);
}

bool	open_squote(t_token *token, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		if (token[j].type == SQUOTE_OPEN)
			while (token[j].type != SQUOTE_CLOSE)
				if (j++ == i)
					return (true);
		j++;
	}
	return (false);
}

bool	open_dquote(t_token *token, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		if (token[j].type == DQUOTE_OPEN)
			while (token[j].type != DQUOTE_CLOSE)
				if (j++ == i)
					return (true);
		j++;
	}
	return (false);
}

bool	open_string(t_token *token, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		if (token[j].type == STRING_OPEN)
			while (token[j].type != STRING_CLOSE)
				if (j++ == i)
					return (true);
		j++;
	}
	return (false);
}
