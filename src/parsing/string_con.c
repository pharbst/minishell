/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_con.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:08:01 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/17 11:52:51 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	string_cmd_arg_con(t_parsing *a, bool *cmd)
{
	if (*a->token_index >= a->token_count
		|| a->token[*a->token_index].type == SPACE
		|| a->token[*a->token_index].type == PIPE
		|| *a->token[*a->token_index].location == '<')
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
	if (*a->token[*a->token_index].location == '>')
	{
		if (/*is filediscriptor*/)					//if it is a filedescriptor its part of the redirection
			printf("filediscriptor found\n");
		else if (*cmd == true)						//when cmd was already found its part of the redirection
		{
			//its part of the redirection
		}
		else
			a->pipex->cmd = ft_substr(a->token[*a->token_index - 2].location, 0,
					(a->token[*a->token_index - 2].location
						- a->token[*a->token_index - 1].location) + 1);
	}
}

static void	string_dollar_con(t_parsing *a, bool *cmd)
{
	if (a->token[*a->token_index].type == DOLLAR)
		//cat string with variable string together
}

static void	string_quotes_con(t_parsing *a, bool *cmd)
{
	if (a->token[*a->token_index].type == DQUOTE_OPEN)
		//cat strings together
	else if (a->token[*a->token_index].type == SQUOTE_OPEN)
		//cat strings together
}

static bool	str_cat(t_parsing *a, char *tmp)
{
	if (*a->token_index >= a->token_count)
		return (true);
	if (a->token[*a->token_index].type == DQUOTE_OPEN)
		tmp = ft_strjoinfree(tmp, quote_expand(a));
}

void	string_condition(t_parsing *a, bool *cmd)
{
	char	*tmp;

	tmp = str_cat(a, cmd);
	if (!tmp)
		return (printf("Error from str_cat tmp = NULL\n"));
	if (a->token[*a->token_index + 1].type == STRING_CLOSE)
		*a->token_index += 2;
	else
		return (printf("string not closed\n"));
	tmp = ft_substr(a->token[*a->token_index - 2].location, 0,
			(a->token[*a->token_index - 2].location
				- a->token[*a->token_index - 1].location) + 1);
	while (!str_cat(a, tmp))
		continue ;
	//check what the string is for and save it in the right place
	if (*a->token_index >= a->token_count)
		return (string_space_pipe_con(a, cmd));
	string_space_pipe_con(a, cmd);
	string_redirect_con(a, cmd);
	string_dollar_con(a, cmd);
	string_quotes_con(a, cmd);
}

//before > only filediscriptors without space are allowed strings before > and before cmd are ignored
