/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:53:03 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/06 18:54:56 by ccompote         ###   ########.fr       */
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


char	*line_with_quotes(char *line)
{
	char 	*new_line;
	int 	i;
	int 	j;

	i = 0;
	j = 0;
	new_line = malloc(sizeof(char) * ft_strlen(line) + 3);
	while (line[j])
	{
		new_line[i] = line[j];
		if (line[j] == '=')
		{
			i++;
			new_line[i] = '"';
		}
		i++;
		j++;
	}
	new_line[i] = '"';
	new_line[++i] = '\0';
	return (new_line);
}

char		**var_export(char **envp, char **argv, int argc)
{
	char	**new_envp;
	int		arraysize;
	int		index;
	char	**name_val;
	int 	flag;
	
	index = 0;
	flag = 0;
	if (argc == 1)
	{
		while (envp[index])
		{
			if (ft_strncmp(envp[index], "_=", 2))
				printf("declare -x %s\n", line_with_quotes(envp[index]));
			index++;
		}
		return (envp);
	}
	else
	{
		name_val = ft_split(argv[1], '=');
		arraysize = get_arraysize(envp);
		new_envp = ft_calloc(arraysize + 2, sizeof(char *));
		if (!new_envp)
			return (NULL);
		while (index < arraysize)
		{
			new_envp[index] = ft_strdup(envp[index]);
			if (!new_envp[index])
				return (NULL);
			if (!ft_strncmp(new_envp[index], name_val[0], ft_strlen(name_val[0])) && new_envp[index][ft_strlen(name_val[0])] == '=')
			{
				new_envp[index] = ft_strdup(argv[1]);
				flag = 1;
			}
			index++;
		}
		if (!flag)
		{	
			new_envp[index] = ft_strdup(argv[1]);
		}
		new_envp[++index] = NULL;
		return (new_envp);
	}
}
