/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:25:11 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/17 17:11:28 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(char *var, char **envp)
{
	char	*tmp;
	int		i;

	tmp = grap(var, envp);
	if (!tmp)
		return (NULL);
	i = 0;
	while (tmp[i] != '=')
		i++;
	return (ft_substr(tmp, i + 1, ft_strlen(tmp) - i));
}
