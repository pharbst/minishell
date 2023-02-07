/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 04:48:53 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/05 06:40:14 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipex	*init_pipex(va_list args, unsigned int count)
{
	t_pipex			*cmd_list;
	unsigned int	i;
	char			*tmp;

	i = 0;
	cmd_list = ft_calloc(count + 1, sizeof(t_pipex));
	while (i < count)
	{
		tmp = va_arg(args, char *);
		if (tmp[1] == 'c')
			cmd_list[i].cmd = ft_strdup(tmp + 2);
		else if (tmp[1] == 'i')
			cmd_list[i].file_in = ft_strdup(tmp + 2);
		else if (tmp[1] == 'o')
			cmd_list[i].file_out = ft_strdup(tmp + 2);
		i++;
	}
	va_end(args);
	return (cmd_list);
}

static unsigned int	count_cmds(va_list	args)
{
	unsigned int	i;

	i = 0;
	while (va_arg(args, char *)[1] == 'c' && va_arg(args, char *) != NULL)
		i++;
	va_end(args);
	return (i);
}

bool	pipex(char **envp, ...)
{
	va_list			args;
	va_list			args_copy;
	t_pipex			*cmd_list;

	va_start(args, envp);
	va_copy(args_copy, args);
	cmd_list = init_pipex(args_copy, count_cmds(args));
}
