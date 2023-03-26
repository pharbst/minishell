/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 00:42:35 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/26 06:02:04 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

t_pipex	*post_check(t_parsing *a, t_pipex *pipex, bool cmd)
{
	if (a->token_index >= a->token_count)
	{
		if (!cmd)
		{
			if (!pipex->out)
				return (free(pipex), NULL);
			else
				return (pipex);
		}
		else
			return (pipex);
	}
	a->token_index += 1;
	if (a->token[a->token_index].type == PIPE)
		ft_syntax_error(a);
	return (pipex);
}

void	case_check(t_parsing *a, t_pipex *pipex, bool *cmd)
{
	if (a->token[a->token_index].type == STRING_OPEN
		|| a->token[a->token_index].type == DQUOTE_OPEN
		|| a->token[a->token_index].type == SQUOTE_OPEN
		|| a->token[a->token_index].type == DOLLAR)
		string_condition(a, cmd, pipex);
	else if (a->token[a->token_index].type == REDIRECT_IN)
		redirect_in_condition(a, pipex);
	else if (a->token[a->token_index].type == REDIRECT_OUT)
		redirect_out_condition(a, pipex, NULL);
	else if (a->token[a->token_index].type == SPACE_START)
		(a->token_index)++;
}
