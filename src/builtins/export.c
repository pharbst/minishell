/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:53:03 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/26 04:56:50 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_line_with_quotes(char *line)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!ft_strchr(line, '='))
		printf("declare -x %s\n", line);
	else
	{
		new_line = ft_calloc(ft_strlen(line) + 3, sizeof(char));
		if (!new_line)
			return ;
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
}

int	valid_var(char *argv)
{
	int	i;

	i = 0;
	if (!ft_isalpha(argv[i]) && argv[i] != '_')
		return (0);
	i++;
	while (argv[i])
	{
		if (argv[i] == '=')
			return (1);
		if (!ft_isalnum(argv[i]) && argv[i] != '_')
			return (0);
		i++;
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

int	var_export(t_shell *shell, char **argv, int argc)
{
	char	**new_envp;
	int		arraysize;
	int		index;
	char	**name_val;
	int		flag;
	int		i;
	int		new;
	int		exit_status;

	i = 1;
	index = 0;
	exit_status = 0;
	if (argc == 1)
	{
		while (shell->envp[index])
		{
			if (ft_strncmp(shell->envp[index], "_=", 2))
				print_line_with_quotes(shell->envp[index]);
			index++;
		}
		return (0);
	}
	else
	{
		arraysize = get_arraysize(shell->envp);
		new_envp = ft_calloc(arraysize + argc, sizeof(char *));
		if (!new_envp)
			return (1);
		while (shell->envp[index])
		{
			new_envp[index] = ft_strdup(shell->envp[index]);
			if (!new_envp[index])
				return (1);
			index++;
		}
		while (argv[i])
		{
			if (valid_var(argv[i]))
			{
				index = 0;
				flag = 0;
				name_val = ft_split(argv[i], '=');
				while (new_envp[index])
				{
					if (!var_new(new_envp[index], name_val[0]))
					{
						if (name_val[1])
						{
							new_envp[index] = ft_strdup(argv[i]);
							flag = 1;
							new = 1;
						}
						else
							new = 0;
					}
					index++;
				}
				if (!flag && new)
					new_envp[index] = ft_strdup(argv[i]);
			}
			else
			{
				ft_putstr_fd("export: `", 2);
				ft_putstr_fd(argv[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				exit_status = 1;
			}
			i++;
		}
		new_envp[++index] = NULL;
		free_envp(shell->envp);
		shell->envp = new_envp;
		return (exit_status);
	}
}
