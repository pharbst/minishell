/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_condition.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:32:34 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/26 06:02:14 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

void	redirect_in_condition(t_parsing *a, t_pipex *pipex)
{
	a->token_index += 1;
	if (a->token[a->token_index].type == NEW_LINE)
		return (ft_syntax_error(a));
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

void	redirect(t_parsing *a, t_redir_out *new)
{
	if (a->token[a->token_index].type != PIPE)
	{
		if (a->token[a->token_index].location
			&& a->token[a->token_index].type == REDIRECT_OUT)
		{
			a->token_index += 1;
			if (a->token[a->token_index].type == PIPE)
				return (ft_syntax_error(a), free(new));
			new->append = true;
		}
		else
			new->append = false;
	}
}

void	redirect_out_condition(t_parsing *a, t_pipex *pipex, char *file1)
{
	t_redir_out	*new;

	new = ft_calloc(1, sizeof(t_redir_out));
	new->fd_left = 1;
	if (file1)
		new->fd_left = ft_atoi(file1);
	if (file1)
		free(file1);
	a->token_index += 1;
	if (a->token[a->token_index].type == NEW_LINE)
		return (free(new), ft_syntax_error(a));
	redirect(a, new);
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
