/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_con.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:08:01 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/19 15:35:47 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	string_condition(t_parsing *a, bool *cmd, t_pipex *pipex)
{
	char	*tmp;

	tmp = str_cat(a);
	if (!tmp)
		return ;
	if (*a->token_index < a->token_count && a->token[*a->token_index].type
		== REDIRECT_OUT && validate_fd(tmp))
		redirect_out_condition(a, pipex, tmp);
	else if (*cmd == false)
	{
		pipex->cmd = tmp;
		pipex->args = join_arg(pipex, tmp);
		*cmd = true;
	}
	else
		pipex->args = join_arg(pipex, tmp);
}
