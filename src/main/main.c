/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 06:27:24 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/21 16:47:30 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_red_out(t_redir_out *r_head)
{
	t_redir_out	*tmp;

	while (r_head)
	{
		tmp = r_head;
		r_head = r_head->next;
		free(tmp->file_right);
		free(tmp);
	}
}

void	free_pipex(t_pipex *p_head)
{
	t_pipex	*tmp;

	while (p_head)
	{
		tmp = p_head;
		p_head = p_head->next;
		// free(tmp->cmd);
		if (tmp->args)
		{
			printf("args: %p\n", tmp->args);
			ft_free_split(tmp->args);
		}
		if (tmp->in)
		{
			printf("in: %p\n", tmp->in);
			free(tmp->in);
		}
		if (tmp->out)
		{
			printf("out: %p\n", tmp->out);
			free_red_out(tmp->out);
		}
		printf("tmp: %p\n", tmp);
		free(tmp);
	}
}

void	ft_exit(t_shell *shell)
{
	free_pipex(shell->p_head);
	printf("user: %p\n", shell->user);
	if (shell->user)
		free(shell->user);
	printf("debug\n");
	if (shell->pwd)
		free(shell->pwd);
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	shell.argv = argv;
	shell.argc = argc;
	shell.envp = envp;
	shell.user = NULL;
	shell.pwd = NULL;
	ft_shell(&shell);
	return (0);
}
