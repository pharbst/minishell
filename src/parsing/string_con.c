/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_con.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:08:01 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/15 16:28:32 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void string_space_pipe_con(t_parsing *parameter, bool *cmd)
{
	if (*parameter->token_index >= parameter->token_count)
	{
		if (*cmd == false)
			printf("cmd found\n");
		else
			printf("cmd argument or path found\n");
	}
	else if (parameter->token[*parameter->token_index].type == SPACE)
	{
		if (*cmd == false)
			printf("cmd found\n");
		else
			printf("cmd argument or path found\n");
	}
	else if (parameter->token[*parameter->token_index].type == PIPE)
	{
		if (*cmd == false)
			printf("cmd found\n");
		else
			printf("cmd argument or path found\n");
	}
}

static void	string_redirect_con(t_parsing *parameter, bool *cmd)
{
	if (*parameter->token[*parameter->token_index].location == '<')
	{
		if (*cmd == false)
			printf("cmd found\n");
		else
			printf("cmd argument or path found\n");
	}
	else if (*parameter->token[*parameter->token_index].location == '>')
	{
		if (/*is filediscriptor*/)
			printf("filediscriptor found\n");
		else
		{
			if (*cmd == false)
				printf("cmd found\n");
			else
			{
				//is part of redirection
			}
		}
	}
}

static void	string_dollar_con(t_parsing *parameter, bool *cmd)
{
	if (parameter->token[*parameter->token_index].type == DOLLAR)
		//cat string with variable string together
}

static void string_quotes_con(t_parsing *parameter, bool *cmd)
{
	if (parameter->token[*parameter->token_index].type == DQUOTE_OPEN)
		//cat strings together
	else if (parameter->token[*parameter->token_index].type == SQUOTE_OPEN)
		//cat strings together
}

void	string_condition(t_parsing *parameter, bool *cmd)
{
	if (parameter->token[*parameter->token_index + 1].type == STRING_CLOSE)
		*parameter->token_index += 2;
	else
		return (printf("string not closed\n"));
	if (*parameter->token_index >= parameter->token_count)
		return (string_space_pipe_con(parameter, cmd));
	string_space_pipe_con(parameter, cmd);
	string_redirect_con(parameter, cmd);
	string_dollar_con(parameter, cmd);
	string_quotes_con(parameter, cmd);
}

//before > only filediscriptors without space are allowed strings before > and before cmd are ignored
