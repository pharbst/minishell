/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:53:22 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/17 15:15:39 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_dollar_var(t_parsing *a)
{
	char	*tmp;
	char	*ret;

	tmp = a->token[*a->token_index].location;
	while (!ft_isspace(*tmp) && *tmp < a->token[*a->token_index + 1].location)
		tmp++;
	ret = get_var(ft_substr(a->token[*a->token_index].location, 1,
				(tmp - a->token[*a->token_index].location) - 1), a->envp);
	a->token[*a->token_index].location = tmp;
	return (ret);
}

char	*quote_expand(t_parsing *a)
{
	char	*tmp;

	tmp = NULL;
	if (a->token[*a->token_index + 1].type == DQUOTE_CLOSE
		|| a->token[*a->token_index + 1].type == SQUOTE_CLOSE)
	{
		*a->token_index += 2;
		return (ft_substr(a->token[*a->token_index - 2].location, 1,
				(a->token[*a->token_index - 1].location
					- a->token[*a->token_index - 2].location) - 1));
	}
	tmp = ft_substr(a->token[*a->token_index].location, 1,
			(a->token[*a->token_index + 1].location
				- a->token[*a->token_index].location) - 1);
	*a->token_index += 1;
	while (a->token[*a->token_index].type != DQUOTE_CLOSE
		|| a->token[*a->token_index].type != SQUOTE_CLOSE)
	{
		if (a->token[*a->token_index].type == DOLLAR)
			tmp = strjoinfree(tmp, expand_dollar_var(a));
		*a->token_index += 1;
	}
}
