/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:31:08 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/29 19:31:15 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tools.h"

int	find_var(char **envp_var, char *var_name)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (envp_var[i] && ft_strncmp(envp_var[i], var_name,
			ft_strlen(var_name)))
		i++;
	if (!envp_var[i])
		return (-1);
	if (envp_var[i][ft_strlen(var_name)] != '=')
	{
		j = find_var(envp_var + i + 1, var_name);
		if (j == -1)
			return (-1);
		i += j + 1;
	}
	return (i);
}

char	*get_var_content(char **envp_var, char *var_name)
{
	int	i;

	i = find_var(envp_var, var_name);
	if (i == -1)
		return (NULL);
	return (ft_substr(ft_strchr(envp_var[i], '='), 1,
			ft_strlen(ft_strchr(envp_var[i], '=') + 1)));
}
