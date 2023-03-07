/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_cat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:53:49 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/07 20:03:12 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*dollar_helper(t_parsing *a, char *tmp)
{
	if (a->token[a->token_index].type == STRING_OPEN)
	{
		tmp = strjoinfree(tmp, ft_substr(a->token[a->token_index].location,
					0, (a->token[a->token_index + 1].location
						- a->token[a->token_index].location) + 1));
		a->token_index += 2;
	}
	else if (a->token[a->token_index].type == DQUOTE_OPEN)
		tmp = strjoinfree(tmp, quote_expand(a));
	else if (a->token[a->token_index].type == SQUOTE_OPEN)
		tmp = strjoinfree(tmp, quote_expand(a));
	return (tmp);
}

static char	*str_cat_helper(t_parsing *a, char *tmp)
{
	char	*tmp2;

	if (a->token[a->token_index].type == STRING_OPEN)
	{
		tmp = strjoinfree(tmp, ft_substr(a->token[a->token_index].location,
					0, (a->token[a->token_index + 1].location
						- a->token[a->token_index].location) + 1));
		a->token_index += 2;
	}
	else if (a->token[a->token_index].type == DQUOTE_OPEN)
		tmp = strjoinfree(tmp, quote_expand(a));
	else if (a->token[a->token_index].type == SQUOTE_OPEN)
		tmp = strjoinfree(tmp, quote_expand(a));
	else if (a->token[a->token_index].type == DOLLAR)
	{
		a->token_index++;
		if (a->token_index < a->token_count
			&& (a->token[a->token_index].type == STRING_OPEN
			|| a->token[a->token_index].type == DQUOTE_OPEN
			|| a->token[a->token_index].type == SQUOTE_OPEN))
		{
			while (a->token_index < a->token_count
				&& a->token[a->token_index].type != REDIRECT_IN
				&& a->token[a->token_index].type != REDIRECT_OUT
				&& a->token[a->token_index].type != PIPE
				&& a->token[a->token_index].type != SPACE_START
				&& a->token[a->token_index].type != DOLLAR)
				tmp2 = dollar_helper(a, tmp2);
			tmp = strjoinfree(tmp, tmp2);
		}
		else
			tmp = ft_strjoinfree(tmp, "$");
	}
		
	return (tmp);
}

char	*str_cat(t_parsing *a)
{
	char	*tmp;

	tmp = NULL;
	while (a->token_index < a->token_count
		&& a->token[a->token_index].type != REDIRECT_IN
		&& a->token[a->token_index].type != REDIRECT_OUT
		&& a->token[a->token_index].type != PIPE
		&& a->token[a->token_index].type != SPACE_START)
	{
		tmp = str_cat_helper(a, tmp);
		if (!tmp)
			return (printf("ERROR: malloc failed in str_cat\n"), NULL);
	}
	return (tmp);
}
