/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:35:57 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/29 19:39:49 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_buildins.h"

int	bi_cd(char **args, int argc, t_shell *shell)
{
	t_cd	a;

	a.o_pwd = pwd();
	a.old_pwd = ft_calloc(3, sizeof(char *));
	a.old_pwd[1] = ft_strjoin("OLDPWD=", a.o_pwd);
	if (argc == 1)
	{
		a.str_dir = get_var_content(shell->envp, "HOME=");
		a.i = chdir(a.str_dir);
		free(a.str_dir);
	}
	else
		a.i = chdir(args[1]);
	if (a.i == -1)
		return (ft_putstrsfd(2, "cd: ", args[1], NO_SUCH_FILE, NULL),
			free(a.old_pwd[1]), free(a.old_pwd), free(a.o_pwd), 1);
	else
		var_export(shell, a.old_pwd, 2);
	a.n_pwd = pwd();
	a.new_pwd = ft_calloc(3, sizeof(char *));
	a.new_pwd[1] = ft_strjoin("PWD=", a.n_pwd);
	var_export(shell, a.new_pwd, 2);
	return (free(a.old_pwd[1]), free(a.old_pwd), free(a.new_pwd[1]),
		free(a.n_pwd), free(a.o_pwd), free(a.new_pwd), 0);
}
