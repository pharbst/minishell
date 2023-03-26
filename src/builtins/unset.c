/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:24:29 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/26 08:29:22 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_buildins.h"

// void	unset(char *var_name, char **env)
// {
// 	size_t	index;
// 	size_t	arraysize;
// 	char	**new_envp;

// 	arraysize = get_arraysize(env);
// 	new_envp = ft_calloc(arraysize, sizeof(char *));
// 	if (!new_envp)
// 		return ;
// 	index = find_var(env, var_name);
// 	ft_memcpy(new_envp, env, (index - 1) * sizeof(char *));
// 	ft_memcpy(new_envp + index, env + index + 1, (arraysize - index)
// 		* sizeof(char *));
// 	env = new_envp;
// 	return ;
// }

int	valid_var_unset(char *argv)
{
	int	i;

	i = 0;
	while (ft_isalpha(argv[i]))
		i++;
	if (i)
		return (1);
	else
		return (0);
}

int	unset(t_shell *shell, char **argv)
{
	int	i;
	int	argc;

	argc = get_arraysize(argv);
	if (argc == 1)
		return (0);
	if (!valid_var_unset(argv[1]))
	{
		ft_putstrsfd(2, "unset: `", argv[1], VAR_NO_VALID, NULL);
		// ft_putstr_fd("unset: `", 2);
		// ft_putstr_fd(argv[1], 2);
		// ft_putstr_fd("': not a valid identifier\n", 2);
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
