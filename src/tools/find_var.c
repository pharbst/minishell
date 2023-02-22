/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:31:08 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/22 16:34:38 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	find_var(char *envp_var, char *var_name)
{
	size_t	i;

	i = 0;
	while (envp_var[i] && !ft_strcmp(envp_var[i], var_name))
		i++;
	if (!envp_var[i])
		return (0);
	return (i);
}
