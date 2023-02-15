/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_con.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:08:01 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/15 17:11:43 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	string_space_pipe_con(t_parsing *a, bool *cmd)
{
	if (*a->token_index >= a->token_count
		|| a->token[*a->token_index].type == SPACE
		|| a->token[*a->token_index].type == PIPE)
	{
		if (*cmd == false)
			a->pipex->cmd = ft_substr(a->token[*a->token_index - 2].location, 0,
					(a->token[*a->token_index - 2].location
						- a->token[*a->token_index - 1].location) + 1);
		else
			a->pipex->args = add_arg(a->pipex->args,
					ft_substr(a->token[*a->token_index - 2].location, 0,
						(a->token[*a->token_index - 2].location
							- a->token[*a->token_index -1].location) + 1));
	}
}

static void	string_redirect_con(t_parsing *a, bool *cmd)
{
	if (*a->token[*a->token_index].location == '<')
	{
		if (*cmd == false)
			a->pipex->cmd = ft_substr(a->token[*a->token_index - 2].location, 0,
					(a->token[*a->token_index - 2].location
						- a->token[*a->token_index - 1].location) + 1);
		else
			a->pipex->args = add_arg(a->pipex->args,
					ft_substr(a->token[*a->token_index - 2].location, 0,
						(a->token[*a->token_index - 2].location
							- a->token[*a->token_index -1].location) + 1));
	}
	else if (*a->token[*a->token_index].location == '>')
	{
		if (/*is filediscriptor*/)
			printf("filediscriptor found\n");
		else
		{
			if (*cmd == false)
				a->pipex->cmd = ft_substr(a->token[*a->token_index - 2].location, 0, (a->token[*a->token_index - 2].location - a->token[*a->token_index - 1].location) + 1);
			else
			{
				//is part of redirection
			}
		}
	}
}

static void	string_dollar_con(t_parsing *a, bool *cmd)
{
	if (a->token[*a->token_index].type == DOLLAR)
		//cat string with variable string together
}

static void string_quotes_con(t_parsing *a, bool *cmd)
{
	if (a->token[*a->token_index].type == DQUOTE_OPEN)
		//cat strings together
	else if (a->token[*a->token_index].type == SQUOTE_OPEN)
		//cat strings together
}

void	string_condition(t_parsing *a, bool *cmd)
{
	if (a->token[*a->token_index + 1].type == STRING_CLOSE)
		*a->token_index += 2;
	else
		return (printf("string not closed\n"));
	if (*a->token_index >= a->token_count)
		return (string_space_pipe_con(a, cmd));
	string_space_pipe_con(a, cmd);
	string_redirect_con(a, cmd);
	string_dollar_con(a, cmd);
	string_quotes_con(a, cmd);
}

//before > only filediscriptors without space are allowed strings before > and before cmd are ignored
