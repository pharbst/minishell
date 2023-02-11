/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 12:14:56 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/11 12:20:09 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	open_quote(t_token *token, unsigned int i)
{
	unsigned int	j;

	j = 0;
	while (j <= i)
	{
		if (token[j].type == DQUOTE_OPEN)
		{
			while (token[j].type != DQUOTE_CLOSE)
				if (j++ == i)
					return (true);
		}
		if (token[j].type == SQUOTE_OPEN)
		{
			while (token[j].type != SQUOTE_CLOSE)
				if (j++ == i)
					return (true);
		}
		j++;	
	}
	return (false);
}
