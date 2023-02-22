/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:36:12 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/22 17:57:56 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

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
	free(shell->user);
	free(shell->pwd);
	free_envp(shell->envp);
	exit(0);
}
