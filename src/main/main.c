/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 06:27:24 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/25 18:17:01 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**malloc_envp(char **envp)
{
	int		i;
	char	**new_envp;

	if (!envp)
		return (ft_calloc(1, sizeof(char *)));
	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	printf("debug\n");
	shell.argv = argv;
	shell.argc = argc;
	shell.envp = malloc_envp(envp);
	shell.user = NULL;
	shell.pwd = NULL;
	get_shell(WRITE, &shell);
	ft_shell(&shell);
	return (0);
}
