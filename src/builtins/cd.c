/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:35:57 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/29 17:49:11 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_buildins.h"

int	bi_cd(char **args, int argc, t_shell *shell)
{
	int		i;
	char	**old_pwd;
	char	**new_pwd;
	char	*n_pwd;
	char	*o_pwd;
	char 	*str_dir;

	o_pwd = pwd();
	old_pwd = ft_calloc(3, sizeof(char *));
	old_pwd[1] = ft_strjoin("OLDPWD=", o_pwd);
	if (argc == 1)
	{
		str_dir = get_var_content(shell->envp, "HOME=");
		i = chdir(str_dir);
		free(str_dir);
	}
	else
		i = chdir(args[1]);
	if (i == -1)
	{
		ft_putstrsfd(2, "cd: ", args[1], NO_SUCH_FILE, NULL);
		return (free(old_pwd[1]), free(old_pwd), free(o_pwd), 1);
	}
	else
		var_export(shell, old_pwd, 2);
	n_pwd = pwd();
	new_pwd = ft_calloc(3, sizeof(char *));
	new_pwd[1] = ft_strjoin("PWD=", n_pwd);
	var_export(shell, new_pwd, 2);
	return (free(old_pwd[1]), free(old_pwd), free(new_pwd[1]), free(n_pwd), free(o_pwd), free(new_pwd),
		0);
}
