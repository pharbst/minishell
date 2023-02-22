/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 06:27:24 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/22 17:56:38 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	shell.argv = argv;
	shell.argc = argc;
	shell.envp = malloc_envp(envp);
	shell.user = NULL;
	shell.pwd = NULL;
	get_shell(WRITE, &shell);
	ft_shell(&shell);
	return (0);
}
