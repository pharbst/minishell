/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 21:14:55 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/17 15:47:36 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

void	ft_shell(t_shell *shell)
{
	while (1)
	{
		prompt_line(shell);
		shell->line = readline(NULL);
		shell->p_head = shell_parsing_main(shell->line, shell->envp);
		// if (!shell->p_head)
			//line too long o other error
		//add history
		//execute cmd
		//prepare for next cmd
	}
}
