/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:24:29 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/22 16:31:58 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(char *var_name, t_shell *shell)
{
	size_t	index;
	size_t	arraysize;
	char	**new_envp;

	arraysize = get_arraysize(shell->envp);
	new_envp = ft_calloc(arraysize, sizeof(char *));
	if (!new_envp)
		return ;
	index = find_var(shell->envp, var_name);
	ft_memcpy(new_envp, shell->envp, (index - 1) * sizeof(char *));
	ft_memcpy(new_envp + index, shell->envp + index + 1, (arraysize - index)
		* sizeof(char *));
	shell->envp = new_envp;
	return ;
}
