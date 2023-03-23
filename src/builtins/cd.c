/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:35:57 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/23 10:37:58 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	else
		shell->envp = var_export(shell->envp, old_pwd, 2);
	new_pwd = ft_calloc(3, sizeof(char *));
	new_pwd[1] = ft_calloc(4 + ft_strlen(pwd()), sizeof(char));
	new_pwd[1] = ft_strjoin("PWD=", pwd());
	shell->envp = var_export(shell->envp, new_pwd, 2);
	return (free(old_pwd[1]), free(old_pwd), free(new_pwd[1]), free(new_pwd),
		0);
}
