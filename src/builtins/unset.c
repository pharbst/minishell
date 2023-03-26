/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:24:29 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/26 12:36:49 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_buildins.h"

int	unset(t_shell *shell, char **argv)
{
	int	i;
	int	argc;

	argc = get_arraysize(argv);
	if (argc == 1)
		return (0);
	if (!valid_var(argv[1]))
	{
		ft_putstrsfd(2, "unset: `", argv[1], VAR_NO_VALID, NULL);
		return (1);
	}
	i = find_var(shell->envp, argv[1]);
	if (i == -1)
		return (0);
	while (shell->envp[i])
	{
		shell->envp[i] = shell->envp[i + 1];
		i++;
	}
	return (0);
}
