/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:36:12 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/28 18:06:50 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_buildins.h"

void	finish_exit(t_shell *shell)
{
	free_pipex(shell);
	free(shell->user);
	free(shell->pwd);
	free_envp(shell->envp);
}

int	ft_exit(int argc, char **args, t_shell *shell)
{
	int	status;

	status = 0;
	if (argc != -1)
		write(2, "exit\n", 5);
	else
		status = shell->exit_status;
	if (argc >= 2 && (!ft_atoi(args[1])
			&& *shell->p_head->args[1] != '0'))
	{
		ft_putstrsfd(2, SHELL_NAME, "exit: ", args[1], EXIT_WRONG_ARG, NULL);
		status = 255;
	}
	else if (argc == 2)
		status = ft_atoi(args[1]);
	else if (argc > 2)
	{
		ft_putstr_fd(EXIT_TOO_MANY_ARGS, 2);
		shell->exit_status = 1;
		return (1);
	}
	finish_exit(shell);
	exit(status);
}
