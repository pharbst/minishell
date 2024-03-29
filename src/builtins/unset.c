/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:24:29 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/29 19:19:41 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_buildins.h"

int	valid_var(char *argv)
{
	int	i;

	i = 0;
	if (!ft_isalpha(argv[i]) && argv[i] != '_')
		return (0);
	i++;
	while (argv[i])
	{
		if (argv[i] == '=')
			return (1);
		if (!ft_isalnum(argv[i]) && argv[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	unset(t_shell *shell, char **argv)
{
	int	i;
	int	argc;

	argc = get_arraysize(argv);
	if (argc == 1)
		return (0);
	if (!valid_var(argv[1]))
		return (ft_putstrsfd(2, "unset: `", argv[1], VAR_NO_VALID, NULL), 1);
	i = find_var(shell->envp, argv[1]);
	if (i == -1)
		return (0);
	free(shell->envp[i]);
	while (shell->envp[i])
	{
		shell->envp[i] = shell->envp[i + 1];
		i++;
	}
	return (0);
}
