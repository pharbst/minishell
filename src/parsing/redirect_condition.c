/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_condition.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:32:34 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/17 19:00:09 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_in_condition(t_parsing *a, t_pipex *pipex)
{
	if (!a)
		return ;
	if (!pipex)
		return ;
	printf("redirect_in_condition\n");
}

void	redirect_out_condition(t_parsing *a, t_pipex *pipex, char *file1)
{
	if (!a)
		return ;
	if (!file1)
		return ;
	if (!pipex)
		return ;
	printf("redirect_out_condition\n");
}
