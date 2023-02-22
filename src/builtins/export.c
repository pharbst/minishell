/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:53:03 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/22 16:02:36 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**export(char **envp, char *var_name, char *var_value)
{
	char	**new_envp;
	size_t	arraysize;
	size_t	index;

	arraysize = get_arraysize(envp);
	new_envp = ft_calloc(arraysize + 2, sizeof(char *));
	if (!new_envp)
		return (NULL);
	index = 0;
	while (index < arraysize)
	{
		new_envp[index] = ft_strdup(envp[index]);
		if (!new_envp[index])
			return (NULL);
		index++;
	}
	new_envp[index] = strjoinfree(ft_strjoinchar(var_name, '='), var_value);
	return (new_envp);
}
