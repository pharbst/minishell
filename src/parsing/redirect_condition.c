/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_condition.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:32:34 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/19 15:28:25 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_in_condition(t_parsing *a, t_pipex *pipex)
{
	*a->token_index += 1;
	if (a->token[*a->token_index].type == SPACE)
		*a->token_index += 1;
	pipex->in = str_cat(a);
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

void	redirect_out_condition(t_parsing *a, t_pipex *pipex, char *file1)
{
	char		*tmp;
	t_redir_out	*new;

	new = ft_calloc(1, sizeof(t_redir_out));
	new->fd_left = 1;
	if (file1)
		new->fd_left = ft_atoi(file1);
	*a->token_index += 1;
	if (*a->token[*a->token_index].location == '&')
	{
		tmp = ft_substr(str_cat(a), 1, ft_strlen(str_cat(a)) - 1);
		if (validate_fd(tmp))
			new->file_right = tmp;
		else
			printf("error: invalid fd\n");
	}
	else
	{
		if (a->token[*a->token_index].type == SPACE)
			*a->token_index += 1;
		new->file_right = str_cat(a);
	}
	add_redir_out(pipex, new);
}
