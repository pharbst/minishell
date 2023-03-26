/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:31:08 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/26 05:50:18 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tools.h"

int	find_var(char **envp_var, char *var_name)
{
	size_t	i;

	i = 0;
	while (envp_var[i] && ft_strncmp(envp_var[i], var_name,
			ft_strlen(var_name)))
		i++;
	if (!envp_var[i])
		return (-1);
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
