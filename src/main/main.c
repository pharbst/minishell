/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 06:27:24 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/06 21:56:14 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->history[i])
		free(shell->history[i++]);
	free(shell->history);
	i = 0;
	while (shell->envp[i])
		free(shell->envp[i++]);
	free(shell->envp);
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	shell.argv = argv;
	shell.argc = argc;
	shell.envp = envp;
	while (1)
		ft_shell(&shell);
	return (0);
}