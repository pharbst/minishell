/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:57:35 by ccompote          #+#    #+#             */
/*   Updated: 2023/03/23 10:40:35 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_builtins(t_pipex *p_head)
{
	if (!ft_strcmp(p_head->cmd, "cd"))
		return (2);
	else if (!ft_strcmp(p_head->cmd, "echo"))
		return (3);
	else if (!ft_strcmp(p_head->cmd, "env"))
		return (4);
	else if (!ft_strcmp(p_head->cmd, "export"))
		return (5);
	else if (!ft_strcmp(p_head->cmd, "pwd"))
		return (6);
	else if (!ft_strcmp(p_head->cmd, "unset"))
		return (7);
	else if (!ft_strcmp(p_head->cmd, "exit"))
		return (8);
	return (0);
}

int	check_before_fork(t_pipex *p_head, char *command)
{
	int	i;

	if (p_head->cmd)
		i = check_builtins(p_head);
	else
		return (1);
	if (i)
		return (i);
	if (!command)
	{
		ft_putstr_fd(p_head->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (0);
	}
	return (1);
}

int	builtin_child(t_pipex *p_head, t_shell *shell, int flag_builtin)
{
	char	*cur_dir;

	if (flag_builtin == 3)
		bi_echo(get_arraysize(p_head->args), p_head->args);
	else if (flag_builtin == 4)
		print_env(shell->envp);
	else if (flag_builtin == 6)
	{
		cur_dir = pwd();
		if (!cur_dir)
			return (1);
		printf("%s\n", cur_dir);
		free(cur_dir);
	}
	return (0);
}

int	builtin_main(t_pipex *p_head, t_shell *shell, int flag_builtin)
{
	if (flag_builtin == 2 && !p_head->next)
	{	
		return (bi_cd(p_head->args, get_arraysize(p_head->args), shell));
	}
	else if (flag_builtin == 5)
	{
		shell->envp = var_export(shell->envp, p_head->args,
				get_arraysize(p_head->args));
		shell->envp_exported = shell->envp;
		return (0);
	}
	else if (flag_builtin == 7)
	{
		shell->envp = unset(shell->envp, p_head->args);
		return (0);
	}
	return (2);
}
