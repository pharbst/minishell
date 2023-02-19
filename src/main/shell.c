/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 21:14:55 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/19 15:28:51 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

void	ft_shell(t_shell *shell)
{
	// while (1)
	// {
		// prompt_line(shell);
		shell->line = readline("minishell$ ");
		// shell->line = ft_strdup("cat tmp >tmp1 2>&1");
		shell->p_head = shell_parsing_main(shell->line, shell->envp);
		print_pipex(shell->p_head);
		// if (!shell->p_head)
			//line too long o other error
		//add history
		//execute cmd
		//prepare for next cmd
	// }
}
