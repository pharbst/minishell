/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:36:12 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/23 15:12:31 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		if (tmp->file_right)
			free(tmp->file_right);
		free(tmp);
	}
}

void	free_pipex(t_shell *shell)
{
	t_pipex	*tmp;

	while (shell->p_head)
	{
		tmp = shell->p_head;
		shell->p_head = shell->p_head->next;
		if (tmp->args)
			ft_free_split(tmp->args);
		if (tmp->in)
			free(tmp->in);
		if (tmp->out)
		{
			free_red_out(tmp->out);
			tmp->out = NULL;
		}
		free(tmp);
	}
	free(shell->p_head);
	shell->p_head = NULL;
}

void	ft_exit(t_shell *shell)
{
	free_pipex(shell);
	free(shell->user);
	free(shell->pwd);
	free_envp(shell->envp);
	exit(0);
}
