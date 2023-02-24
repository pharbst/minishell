/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_cat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:53:49 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/20 20:52:22 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*str_cat_helper(t_parsing *a, char *tmp)
{
	// print_token_type(a->token[a->token_index]);
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
		tmp = strjoinfree(tmp, get_var(ft_substr(a->token[a->token_index]
						.location, 1, (a->token[a->token_index + 1]
							.location - a->token[a->token_index]
							.location) - 1), a->envp));
	return (tmp);
}

char	*str_cat(t_parsing *a)
{
	char	*tmp;

	tmp = NULL;
	while (a->token_index < a->token_count
		&& a->token[a->token_index].type != REDIRECT_OUT
		&& a->token[a->token_index].type != PIPE
		&& a->token[a->token_index].type != SPACE_START
		&& a->token[a->token_index].type != REDIRECT_IN)
	{
		tmp = str_cat_helper(a, tmp);
		if (!tmp)
			return (printf("ERROR: malloc failed in str_cat\n"), NULL);
	}
	return (tmp);
}
