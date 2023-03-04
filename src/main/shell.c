/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 21:14:55 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/04 15:01:03 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

void	shell_readline(t_shell *shell)
{
	char	*line;

	line = get_prompt_line(shell);
	shell->line = readline(line);
	free(line);
}

void	shell_interactive(t_shell *shell)
{
	while (1)
	{
		shell_readline(shell);
		// shell->line = ft_strdup("ls >tmp | cat tmp");
		shell->p_head = shell_parsing_main(shell->line, shell->envp);
		// printf("\n\n\n");
		// print_pipex(shell->p_head);
		if (!ft_strcmp(shell->p_head->cmd, "exit"))
		{
			printf("exit\n");
			break ;
		}
		execute(shell->p_head, shell->envp);
		// if (!shell->p_head)
			//line too long o other error
		//add history
		free_pipex(shell->p_head);
	}
	ft_exit(shell);
}

void	shell_alone(t_shell *shell)
{
	int	i;

	i = 1;
	shell->line = ft_strjoin(shell->argv[i], " ");
	while (shell->argv[++i])
		shell->line = ft_strjoinfree(shell->line, shell->argv[i]);
	shell->p_head = shell_parsing_main(shell->line, shell->envp);
	execute(shell->p_head, shell->envp);
	ft_exit(shell);
}
