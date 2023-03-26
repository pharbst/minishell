/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_con.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:08:01 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/26 04:16:57 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	string_condition(t_parsing *a, bool *cmd, t_pipex *pipex)
{
	char	*tmp;

	tmp = str_cat(a);
	if (!tmp)
		return ;
	if (a->token_index < a->token_count && a->token[a->token_index].type
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
