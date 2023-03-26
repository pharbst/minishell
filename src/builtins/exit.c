/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:36:12 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/26 06:24:33 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_buildins.h"

void	ft_exit(t_shell *shell)
{
	free_pipex(shell);
	free(shell->user);
	free(shell->pwd);
	free_envp(shell->envp);
	exit(0);
}
