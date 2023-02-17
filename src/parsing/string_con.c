/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_con.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:08:01 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/17 19:27:58 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_cat(t_parsing *a)
{
	char	*tmp;

	printf("enter str_cat\n");
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
			tmp = strjoinfree(tmp, quote_expand(a));
		else if (a->token[*a->token_index].type == SQUOTE_OPEN)
			tmp = strjoinfree(tmp, quote_expand(a));
		else if (a->token[*a->token_index].type == DOLLAR)
			tmp = strjoinfree(tmp, get_var(ft_substr(a->token[*a->token_index]
							.location, 1, (a->token[*a->token_index + 1]
								.location - a->token[*a->token_index]
								.location) - 1), a->envp));
		if (!tmp)
			return (printf("ERROR: malloc failed in str_cat\n"), NULL);
	}
	return (tmp);
}

void	string_condition_helper1(t_parsing *a, bool *cmd, t_pipex *pipex,
		char *tmp)
{
	printf("enter string_condition_helper1\n");
	if (*a->token_index < a->token_count && a->token[*a->token_index].type
		== REDIRECT_OUT && validate_fd(tmp))
		redirect_out_condition(a, pipex, tmp);
	else
	{
		pipex->cmd = tmp;
		*cmd = true;
	}
}

void	string_condition_helper2(t_parsing *a, t_pipex *pipex, char *tmp)
{
	printf("enter string_condition_helper2\n");
	if (*a->token_index < a->token_count && a->token[*a->token_index].type
		== REDIRECT_OUT)
		redirect_out_condition(a, pipex, tmp);
	else
		pipex->args = join_arg(pipex, tmp);
}

void	string_condition(t_parsing *a, bool *cmd, t_pipex *pipex)
{
	char	*tmp;

	printf("enter string_condition\n");
	tmp = str_cat(a);
	if (!tmp)
		return ;

	if (*cmd == false)
		string_condition_helper1(a, cmd, pipex, tmp);
	else
		string_condition_helper2(a, pipex, tmp);
}
