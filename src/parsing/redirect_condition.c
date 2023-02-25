/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_condition.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:32:34 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/25 18:06:31 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_in_condition(t_parsing *a, t_pipex *pipex)
{
	a->token_index += 1;
	if (a->token[a->token_index].type == REDIRECT_IN)
		hdc(a, pipex);
	else
	{
		if (a->token[a->token_index].type == SPACE_START)
			a->token_index += 1;
		pipex->in = str_cat(a);
		if (pipex->fd_in)
			close(pipex->fd_in);
	}
}

static void	add_redir_out(t_pipex *pipex, t_redir_out *new)
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

static bool	red_helper(t_parsing *a, t_redir_out *new)
{
	char	*tmp;

	if (a->token[a->token_index].type == SPACE_START)
		a->token_index += 1;
	tmp = str_cat(a);
	if (*tmp == '&')
		return (printf("minishell: syntax error near unexpected token `&'\n")
			, true);
	else
		new->file_right = tmp;
	return (false);
}

static bool	red_helper2(t_parsing *a, t_redir_out *new)
{
	char	*tmp;
	char	*tmp1;

	tmp = str_cat(a);
	tmp1 = ft_substr(tmp, 1, ft_strlen(tmp) - 1);
	free(tmp);
	if (validate_fd(tmp1))
		new->file_right = tmp1;
	else
		return (printf("minishell: %d: Bad file descriptor\n"
				, ft_atoi(tmp1)), true);
	return (false);
}

void	redirect_out_condition(t_parsing *a, t_pipex *pipex, char *file1)
{
	t_redir_out	*new;

	new = ft_calloc(1, sizeof(t_redir_out));
	new->fd_left = 1;
	if (a->token[a->token_index].location
		&& *a->token[a->token_index].location == '>')
		new->append = true;
	else
		new->append = false;
	if (file1)
		new->fd_left = ft_atoi(file1);
	if (file1)
		free(file1);
	a->token_index += 1;
	if (a->token[a->token_index].location
		&& *a->token[a->token_index].location == '&')
	{
		if (red_helper2(a, new))
			return ;
	}
	else if (red_helper(a, new))
		return ;
	add_redir_out(pipex, new);
}
