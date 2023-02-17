/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:53:22 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/17 19:28:36 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_dollar_var(t_parsing *a)
{
	char	*tmp;
	// char	*ret;

	printf("enter expand_dollar_var\n");
	tmp = a->token[*a->token_index].location;
	while (!ft_isspace(*tmp) && tmp < a->token[*a->token_index + 1].location)
		tmp++;
	// ret = get_var(ft_substr(a->token[*a->token_index].location, 1,
				// (tmp - a->token[*a->token_index].location) - 1), a->envp);
	printf("get_var not implemented yet\n");
	a->token[*a->token_index].location = tmp;
	// return (ret);
	return (printf("return value not implemented yet\n"), NULL);
}

char	*quote_expand(t_parsing *a)
{
	char	*tmp;

	printf("enter quote_expand\n");
	tmp = NULL;
	if (a->token[*a->token_index + 1].type == DQUOTE_CLOSE
		|| a->token[*a->token_index + 1].type == SQUOTE_CLOSE)
	{
		*a->token_index += 2;
		return (ft_substr(a->token[*a->token_index - 2].location, 1,
				(a->token[*a->token_index - 1].location
					- a->token[*a->token_index - 2].location) - 1));
	}
	while (a->token[*a->token_index].type != DQUOTE_CLOSE
		|| a->token[*a->token_index].type != SQUOTE_CLOSE)
	{
		tmp = ft_substr(a->token[*a->token_index].location, 1,
				(a->token[*a->token_index + 1].location
					- a->token[*a->token_index].location) - 1);
		*a->token_index += 1;
		if (a->token[*a->token_index].type == DOLLAR)
			tmp = strjoinfree(tmp, expand_dollar_var(a));
	}
	return (tmp);
}
