/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 06:27:24 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/02 13:06:30 by ccompote         ###   ########.fr       */
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

static bool	check_interactive(int argc, char **argv)
{
	if (argc == 1)
		return (true);
	if (argc == 2 && !ft_strncmp(argv[1], "-c", 2))
		return (false);
	return (true);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	shell.argv = argv;
	shell.argc = argc;
	shell.envp = malloc_envp(envp);
	shell.user = NULL;
	shell.pwd = NULL;
	get_shell(WRITE, &shell);
	if (check_interactive(argc, argv))
		shell_interactive(&shell);
	else
		shell_alone(&shell);
	return (0);
}
