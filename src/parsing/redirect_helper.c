/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 03:05:25 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/26 06:02:18 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

void	add_redir_out(t_pipex *pipex, t_redir_out *new)
{
	t_redir_out	*tmp;

	if (!pipex->out)
		pipex->out = new;
	else
	{
		tmp = pipex->out;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

bool	red_helper(t_parsing *a, t_redir_out *new)
{
	char	*tmp;

	if (a->token[a->token_index].type == PIPE)
		a->token_index += 1;
	if (a->token[a->token_index].type == SPACE_START)
		a->token_index += 1;
	tmp = str_cat(a);
	if (!tmp || *tmp == '&')
		return (free(new), ft_syntax_error(a), true);
	if (*tmp == '&')
		return (printf("minishell: syntax error near unexpected token `&'\n"),
			free(new), true);
	else
		new->file_right = tmp;
	return (false);
}

bool	red_helper2(t_parsing *a, t_redir_out *new)
{
	char	*tmp;
	char	*tmp1;

	tmp = str_cat(a);
	tmp1 = ft_substr(tmp, 0, ft_strlen(tmp));
	free(tmp);
	if (validate_fd(tmp1 + 1))
		new->file_right = tmp1;
	else
		return (printf("minishell: %d: Bad file descriptor\n"
				, ft_atoi(tmp1)), true);
	return (false);
}
