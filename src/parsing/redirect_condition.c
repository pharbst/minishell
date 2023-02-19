/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_condition.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:32:34 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/19 14:38:09 by pharbst          ###   ########.fr       */
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

void	redirect_out_condition(t_parsing *a, t_pipex *pipex, char *file1)
{
	char	*tmp;

	pipex->out->fd_left = 1;
	if (file1)
		pipex->out->fd_left = ft_atoi(file1);
	*a->token_index += 1;
	if (*a->token[*a->token_index].location == '&')
	{
		tmp = ft_substr(str_cat(a), 1, ft_strlen(str_cat(a)) - 1);
		if (validate_fd(tmp))
			pipex->out->file_right = tmp;
		else
			printf("error: invalid fd\n");
	}
	else
	{
		if (a->token[*a->token_index].type == SPACE)
			*a->token_index += 1;
		pipex->out->file_right = str_cat(a);
	}
}
