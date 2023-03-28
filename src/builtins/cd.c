/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:35:57 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/28 18:04:17 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_buildins.h"

int	bi_cd(char **args, int argc, t_shell *shell)
{
	int		i;
	char	**old_pwd;
	char	**new_pwd;

	old_pwd = ft_calloc(3, sizeof(char *));
	old_pwd[1] = ft_calloc(7 + ft_strlen(pwd()), sizeof(char));
	old_pwd[1] = ft_strjoin("OLDPWD=", pwd());
	if (argc == 1)
		i = chdir(get_var_content(shell->envp, "HOME="));
	else
		i = chdir(args[1]);
	if (i == -1)
	{
		ft_putstrsfd(2, "cd: ", args[1], NO_SUCH_FILE, NULL);
		return (1);
	}
	else
		var_export(shell, old_pwd, 2);
	new_pwd = ft_calloc(3, sizeof(char *));
	new_pwd[1] = ft_calloc(4 + ft_strlen(pwd()), sizeof(char));
	new_pwd[1] = ft_strjoin("PWD=", pwd());
	var_export(shell, new_pwd, 2);
	return (free(old_pwd[1]), free(old_pwd), free(new_pwd[1]), free(new_pwd),
		0);
}
