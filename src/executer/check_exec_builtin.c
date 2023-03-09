/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:57:35 by ccompote          #+#    #+#             */
/*   Updated: 2023/03/09 23:27:45 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_before_fork(t_pipex *p_head, char *command)
{
	int i;

	if (p_head->cmd)
		i = check_builtins(p_head);
	else
		return (1);
	if (i)
		return (i);
	if (!command)
	{
		printf("%s: command not found\n", p_head->cmd);
		return (0);
	}
	return (1);
}

int check_builtins(t_pipex *p_head)
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

void builtin_child(t_pipex *p_head, t_shell *shell, int flag_builtin)
{
	if (flag_builtin == 3)
		bi_echo(get_arraysize(p_head->args), p_head->args);
	else if (flag_builtin == 4)
		print_env(shell->envp);
	else if (flag_builtin == 6)
		printf("%s\n", pwd());
}

int builtin_main(t_pipex *p_head, t_shell *shell, int flag_builtin)
{
	if (flag_builtin == 2 && !p_head->next)
	{
		bi_cd(p_head->args, get_arraysize(p_head->args), shell);
		return (1);
	}
	else if (flag_builtin == 5)
	{
		shell->envp = var_export(shell->envp, p_head->args, get_arraysize(p_head->args));
		return (1);
	}
	else if (flag_builtin == 7)
	{
		shell->envp = unset( shell->envp, p_head->args);
		return (1);
	}
	return (0);
}