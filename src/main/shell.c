/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 21:14:55 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/08 20:39:20 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

void	ft_shell(t_shell *shell)
{
	prompt_line(shell);
	// shell->line = ft_strdup("Hallo < tmp > tmp1 | World < tmp2 > tmp3 | Bye");
	shell->line = readline(NULL);
	shell_split(shell->line);
}