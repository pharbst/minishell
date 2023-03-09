/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 02:56:28 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/09 23:02:03 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*grap(char *str, char **envp)
{
	int	i;
	int	j;

	if (!str || !envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] == str[j])
			j++;
		if (!str[j])
			return (envp[i]);
		i++;
	}
	return (NULL);
}
