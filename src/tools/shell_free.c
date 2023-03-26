/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 05:06:23 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/26 05:47:42 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tools.h"

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
