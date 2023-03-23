/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:24:29 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/23 09:50:33 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	**unset(char **envp, char **argv)
{
	int	i;
	int	argc;

	argc = get_arraysize(argv);
	if (argc == 1)
		return (envp);
	i = find_var(envp, argv[1]);
	if (i == -1)
		return (envp);
	while (envp[i])
	{
		envp[i] = envp[i + 1];
		i++;
	}
	return (envp);
}
