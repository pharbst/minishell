/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:24:29 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/03 17:00:03 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(char *var_name, char **env)
{
	size_t	index;
	size_t	arraysize;
	char	**new_envp;

	arraysize = get_arraysize(env);
	new_envp = ft_calloc(arraysize, sizeof(char *));
	if (!new_envp)
		return ;
	index = find_var(env, var_name);
	ft_memcpy(new_envp, env, (index - 1) * sizeof(char *));
	ft_memcpy(new_envp + index, env + index + 1, (arraysize - index)
		* sizeof(char *));
	env = new_envp;
	return ;
}
