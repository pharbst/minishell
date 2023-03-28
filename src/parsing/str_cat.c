/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_cat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:53:49 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/28 13:36:12 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

char	*dollar_helper(t_parsing *a, char *tmp)
{
	int		i;
	char	*tmp2;

	i = 0;
	if (a->token[a->token_index].location[i] == '?')
	{
		tmp = strjoinfree(tmp, ft_itoa(a->exit_status));
		i++;
	}
	else
	{
		while (ft_isalnum(a->token[a->token_index].location[i])
			|| a->token[a->token_index].location[i] == '_')
			i++;
		tmp2 = ft_substr(a->token[a->token_index].location, 0, i);
		tmp = strjoinfree(tmp, get_var_content(a->envp, tmp2));
		free(tmp2);
	}
	if (&a->token[a->token_index].location[i]
		< a->token[a->token_index + 1].location)
		a->token[a->token_index].location
			= &a->token[a->token_index].location[i];
	else
		a->token_index += 2;
	return (tmp);
}

char	*str_cat_helper(t_parsing *a, char *tmp)
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
	else if (a->token[a->token_index].type == DOLLAR)
	{
		a->token_index++;
		if (a->token[a->token_index].type != STRING_OPEN)
		{
			if (a->token[a->token_index].type == DQUOTE_OPEN
				||a->token[a->token_index].type == SQUOTE_OPEN)
				return (tmp);
			return (ft_strjoinfree(tmp, "$"));
		}
		tmp = dollar_helper(a, tmp);
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
			// return (printf("ERROR: malloc failed in str_cat\n"), NULL);
			return (NULL);
	}
	return (tmp);
}
