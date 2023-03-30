/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:53:22 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/30 16:34:21 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

char	*expand_dollar_var(t_parsing *a)
{
	char	*tmp;
	char	*ret;
	int		i;

	i = 1;
	if (a->token[a->token_index].location[i] == '?')
		return (ft_itoa(a->exit_status));
	if (!ft_isalnum(a->token[a->token_index].location[i]))
		return (ft_strdup("$"));
	while (ft_isalnum(a->token[a->token_index].location[i])
		&& *(a->token[a->token_index].location + i) != '\0'
		&& a->token_index < (a->token_count - 1)
		&& (a->token[a->token_index].location + i)
		< a->token[a->token_index + 1].location)
		i++;
	tmp = ft_substr(a->token[a->token_index].location, 1, i - 1);
	ret = get_var_content(a->envp, tmp);
	return (free(tmp), ret);
}

char	*dquote_expand(t_parsing *a)
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

char	*squote_expand(t_parsing *a)
{
	char	*tmp;

	tmp = NULL;
	while (a->token[a->token_index].type != SQUOTE_CLOSE)
	{
		tmp = strjoinfree(tmp, ft_substr(a->token[a->token_index].location,
					0, (a->token[a->token_index + 1].location
						- a->token[a->token_index].location)));
		a->token_index += 1;
	}
	tmp = ft_strtrim(tmp, "'");
	a->token_index += 1;
	return (tmp);
}
