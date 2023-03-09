/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:14:10 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/09 23:02:03 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**join_arg(t_pipex *pipex, char *tmp)
{
	char	**new;
	int		i;

	if (!tmp)
		return (pipex->args);
	if (!pipex->args)
		return (pipex->args = ft_calloc(2, sizeof(char *)),
			pipex->args[0] = tmp, pipex->args);
	i = 0;
	while (pipex->args[i])
		i++;
	new = ft_calloc(i + 2, sizeof(char *));
	ft_memmove(new, pipex->args, i * sizeof(char *));
	new[i] = tmp;
	return (free(pipex->args), pipex->args = new, pipex->args);
}
