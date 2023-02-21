/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 21:14:55 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/21 16:03:07 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

void	ft_shell(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = get_prompt_line(shell);
		shell->line = readline(line);
		free(line);
		// shell->line = ft_strdup("ls >tmp | cat tmp >tmp1 2>&1");
		shell->p_head = shell_parsing_main(shell->line, shell->envp);
		printf("\n\n\n");
		print_pipex(shell->p_head);
		// if (!shell->p_head)
			//line too long o other error
		if (!strcmp(shell->p_head->cmd, "exit"))
			break ;
		//execute cmd
		free_pipex(shell->p_head);
		// free(shell->line);
		//add history
		//prepare for next cmd
	}
	ft_exit(shell);
}
