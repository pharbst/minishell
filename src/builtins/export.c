/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:53:03 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/05 16:09:38 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	**var_export(char **envp, char *var_name, char *var_value)
// {
// 	char	**new_envp;
// 	int		arraysize;
// 	int		index;

// 	arraysize = get_arraysize(envp);
// 	new_envp = ft_calloc(arraysize + 2, sizeof(char *));
// 	if (!new_envp)
// 		return (NULL);
// 	index = 0;
// 	while (index < arraysize)
// 	{
// 		new_envp[index] = ft_strdup(envp[index]);
// 		if (!new_envp[index])
// 			return (NULL);
// 		index++;
// 	}
// 	new_envp[index] = strjoinfree(ft_strjoinchar(var_name, '='), var_value);
// 	return (new_envp);
// }


char		**var_export(char **envp, char **argv, int argc)
{
	char	**new_envp;
	int		arraysize;
	int		index;
	
	index = 0;
	if (argc == 1)
	{
		while (envp[index])
		{
			if (ft_strncmp(envp[index], "_=", 2))
				printf("%s\n", envp[index]);
			index++;
		}
		return (envp);
	}
	else
	{
		arraysize = get_arraysize(envp);
		new_envp = ft_calloc(arraysize + 2, sizeof(char *));
		if (!new_envp)
			return (NULL);
		while (index < arraysize)
		{
			new_envp[index] = ft_strdup(envp[index]);
			if (!new_envp[index])
				return (NULL);
			index++;
		}
		new_envp[index] = argv[1];
		new_envp[++index] = NULL;
		printf("%i\n", index);
		printf("%s\n", argv[1]);
		int i = 0;
		while (new_envp[i])
		{
			printf("%s\n", new_envp[i]);
			i++;
		}
		return (new_envp);
	}
}
