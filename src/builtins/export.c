/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:53:03 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/29 18:45:58 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_buildins.h"

void	print_line_with_quotes(char *line)
{
	char	*new_line;

	new_line = ft_substr(line, 0, ft_strchr(line, '=') - line);
	new_line = ft_strjoinchar(new_line, '"');
	new_line = ft_strjoinfree(new_line, ft_strchr(line, '=') + 1);
	new_line = ft_strjoinchar(new_line, '"');
	printf("declare -x %s\n", new_line);
	free(new_line);
}

int	line_with_quotes(char *line)
{
	if (!ft_strchr(line, '='))
		printf("declare -x %s\n", line);
	else
		print_line_with_quotes(line);
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
