/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:53:03 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/28 19:59:13 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_buildins.h"

void	print_line_with_quotes(char *line, char *new_line)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
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
	printf("declare -x %s\n", new_line);
	free(new_line);
}

int	line_with_quotes(char *line)
{
	char	*new_line;

	if (!ft_strchr(line, '='))
		printf("declare -x %s\n", line);
	else
	{
		new_line = ft_calloc(ft_strlen(line) + 3, sizeof(char));
		if (!new_line)
			return (0);
		print_line_with_quotes(line, new_line);
	}
	return (1);
}

int	var_new(char *env, char *name)
{
	int	new;

	if (!ft_strncmp(env, name, ft_strlen(name)) && (env[ft_strlen(name)] == '='
			|| env[ft_strlen(name)] == '\0'))
		new = 0;
	else
		new = 1;
	return (new);
}

int	export_alone(char **envp)
{
	int	index;
	int	k;

	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "_=", 2))
		{
			k = line_with_quotes(envp[index]);
			if (!k)
				return (1);
		}
		index++;
	}
	return (0);
}

int	var_export(t_shell *shell, char **argv, int argc)
{
	if (argc == 1)
		return (export_alone(shell->envp));
	else
		return (export_args(shell, argv, argc));
}
