/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 19:58:19 by ccompote          #+#    #+#             */
/*   Updated: 2023/03/29 18:45:45 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_buildins.h"

int	export_new(char **new_envp, int index, char *argv)
{
	new_envp[index] = ft_strdup(argv);
	if (!new_envp[index])
		return (-1);
	return (index);
}

int	export_dups(char **new_envp, char *argv, char **name_val, int flag)
{
	int	index;
	int	new;

	index = 0;
	new = 1;
	while (new_envp[index])
	{
		if (!var_new(new_envp[index], name_val[0]))
		{
			if (name_val[1] || argv[ft_strlen(name_val[0])] == '=')
			{
				free(new_envp[index]);
				new_envp[index] = ft_strdup(argv);
				if (!new_envp[index])
					return (-1);
				flag = 1;
				new = 0;
			}
		}
		index++;
	}
	if (!flag && new)
		return (export_new(new_envp, index, argv));
	return (index);
}

int	export_valid_arg(char *argv, char **new_envp)
{
	int		index;
	int		flag;
	char	**name_val;

	flag = 0;
	name_val = ft_split(argv, '=');
	if (!name_val)
		return (-1);
	index = export_dups(new_envp, argv, name_val, flag);
	free_envp(name_val);
	return (index);
}

int	export_singe_arg(char **new_envp, char **argv, t_shell *shell, int index)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	while (argv[i])
	{
		if (valid_var(argv[i]))
		{
			index = export_valid_arg(argv[i], new_envp);
			if (index == -1)
				return (1);
		}
		else
		{
			ft_putstrsfd(2, "export: `", argv[i], VAR_NO_VALID, NULL);
			exit_status = 1;
		}
		i++;
	}
	new_envp[++index] = NULL;
	shell->envp = new_envp;
	return (exit_status);
}

int	export_args(t_shell *shell, char **argv, int argc)
{
	char	**new_envp;
	int		arraysize;
	int		index;

	index = 0;
	arraysize = get_arraysize(shell->envp);
	new_envp = ft_calloc(arraysize + argc, sizeof(char *));
	if (!new_envp)
		return (1);
	while (shell->envp[index])
	{
		new_envp[index] = ft_strdup(shell->envp[index]);
		free(shell->envp[index]);
		if (!new_envp[index])
			return (1);
		index++;
	}
	free(shell->envp);
	return (export_singe_arg(new_envp, argv, shell, index));
}
