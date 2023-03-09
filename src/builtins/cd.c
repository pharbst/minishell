/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:35:57 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/09 23:27:49 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	bi_cd(char **args, int argc, t_shell *shell)
{
	int i;

	if (argc == 1)
		i = chdir(get_var_content(shell->envp, "HOME="));
	else
		i = chdir(args[1]);
	return (i);
}
