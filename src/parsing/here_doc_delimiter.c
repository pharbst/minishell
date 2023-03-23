/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_delimiter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 23:23:50 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/23 09:42:00 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*hdc_dollar(t_parsing *a)
{
	a->token_index += 1;
	return (ft_strdup("$"));
}

char	*hdc_string(t_parsing *a)
{
	char	*tmp;

	tmp = ft_substr(a->token[a->token_index].location, 0,
			a->token[a->token_index + 1].location
			- a->token[a->token_index].location + 1);
	a->token_index += 2;
	return (tmp);
}

char	*hdc_dquote(t_parsing *a)
{
	char	*tmp;
	int		i;

	i = 1;
	while (a->token[a->token_index + i].type != DQUOTE_CLOSE)
		i++;
	tmp = ft_substr(a->token[a->token_index].location, 1,
			(a->token[a->token_index + i].location
				- a->token[a->token_index].location) - 1);
	a->token_index += i + 1;
	return (tmp);
}

char	*hdc_squote(t_parsing *a)
{
	char	*tmp;
	int		i;

	i = 1;
	while (a->token[a->token_index + i].type != SQUOTE_CLOSE)
		i++;
	tmp = ft_substr(a->token[a->token_index].location, 1,
			(a->token[a->token_index + i].location
				- a->token[a->token_index].location) - 1);
	a->token_index += i + 1;
	return (tmp);
}
