/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:53:22 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/23 09:44:09 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*expand_dollar_var(t_parsing *a)
{
	char	*tmp;
	char	*ret;
	int		i;

	i = 1;
	while (!ft_isspace(*(a->token[a->token_index].location + i))
		&& *(a->token[a->token_index].location + i) != '\0'
		&& a->token_index < (a->token_count - 1)
		&& (a->token[a->token_index].location + i)
		< a->token[a->token_index + 1].location)
		i++;
	tmp = ft_substr(a->token[a->token_index].location, 1, i - 1);
	ret = get_var_content(a->envp, tmp);
	return (free(tmp), ret);
}

char	*quote_expand(t_parsing *a)
{
	char	*tmp;

	tmp = NULL;
	if (a->token[a->token_index + 1].type == DQUOTE_CLOSE
		|| a->token[a->token_index + 1].type == SQUOTE_CLOSE)
	{
		a->token_index += 2;
		return (ft_substr(a->token[a->token_index - 2].location, 1,
				(a->token[a->token_index - 1].location
					- a->token[a->token_index - 2].location) - 1));
	}
	while (a->token[a->token_index].type != DQUOTE_CLOSE
		&& a->token[a->token_index].type != SQUOTE_CLOSE)
	{
		if (a->token[a->token_index].type == DOLLAR)
			tmp = strjoinfree(tmp, expand_dollar_var(a));
		else
			tmp = strjoinfree(tmp, ft_substr(a->token[a->token_index].location,
						1, (a->token[a->token_index + 1].location
							- a->token[a->token_index].location) - 1));
		a->token_index += 1;
	}
	a->token_index += 1;
	return (tmp);
}
