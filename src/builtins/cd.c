/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:35:57 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/04 15:24:18 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_cd(char **args, int argc, char **envp)
{
	int i;

	if (argc == 1)
	{
		i = chdir(get_var_content(envp, "HOME="));
		return (i);
	}
	else
	{
		i = chdir(args[1]);
		return (i);
	}
}
