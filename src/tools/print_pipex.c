/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:39:27 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/19 14:58:57 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_args(char **args)
{
	int	i;

	i = 0;
	if (args)
	{
		while (args[i])
		{
			printf("arg[%d]: %s\n", i, args[i]);
			i++;
		}
	}
	else
		printf("args: (null)\n");
}

void	print_redirection_out(t_redir_out *out)
{
	if (!out)
		printf("out: (null)\n");
	while (out)
	{
		printf("from: %d\n", out->fd_left);
		printf("to: %s\n", out->file_right);
		out = out->next;
	}
}

void	print_pipex(t_pipex *p_head)
{
	if (p_head)
	{
		while (p_head)
		{
			printf("cmd: %s\n", p_head->cmd);
			printf("in: %s\n", p_head->in);
			print_redirection_out(p_head->out);
			print_args(p_head->args);
			printf("\n");
			p_head = p_head->next;
		}
	}
	else
		printf("p_head: (null)\n");
}
