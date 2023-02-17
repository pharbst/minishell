/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_con.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:08:01 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/17 13:00:58 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_cat(t_parsing *a)
{
	char	*tmp;

	tmp = NULL;
	while (*a->token_index < a->token_count && a->token[*a->token_index].type
		!= REDIRECT_OUT && a->token[*a->token_index].type != PIPE
		&& a->token[*a->token_index].type != SPACE)
	{
		if (a->token[*a->token_index].type == STRING_OPEN)
		{
			tmp = strjoinfree(tmp, ft_substr(a->token[*a->token_index].location,
						0, (a->token[*a->token_index + 1].location
							- a->token[*a->token_index].location) + 1));
			*a->token_index += 2;
		}
		else if (a->token[*a->token_index].type == DQUOTE_OPEN)
			tmp = strjoinfree(tmp, dquote_expand(a));
		else if (a->token[*a->token_index].type == SQUOTE_OPEN)
			tmp = strjonfree(tmp, squote_expand(a));
		else if (a->token[*a->token_index].type == DOLLAR)
			tmp = strjoinfree(tmp, dollar_expand(a));
		if (!tmp)
			return (printf("ERROR: malloc failed in str_cat"), NULL);
	}
	return (tmp);
}

void	string_condition(t_parsing *a, bool *cmd)
{
	char	*tmp;

	tmp = str_cat(a);
	if (!tmp)
		return (printf("Error from str_cat tmp = NULL\n"));
	else if (*a->token_index < a->token_count && validate_fd(tmp)
		&& a->token[*a->token_index].type == REDIRECT_OUT)
		printf("redirect filediscriptor\n");
	else if (*a->token_index < a->token_count && *cmd == true
		&& a->token[*a->token_index + 1].type == REDIRECT_OUT)
		printf("redirect file\n");
	else if (*cmd == false)
	{
		a->pipex->cmd == tmp;
		*cmd = true;
	}
	else
		a->pipex->args = join_arg(a, tmp);
}

//before cmd was found only fd without space are allowed before >
