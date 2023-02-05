/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 01:48:44 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/05 03:12:35 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt_line(t_shell *shell)
{
	ft_printf("%s@minishell %s %% ", last_word(grap("USER", shell->envp)), last_word(grap("PWD", shell->envp)));
}