/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 01:48:44 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/23 17:14:57 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt_line(t_shell *shell)
{
	char	*line;
	char	*pwd;
	char	*tmp;
	char	*usr;

	tmp = getcwd(NULL, 0);
	pwd = last_word(tmp);
	usr = get_var_content(shell->envp, "USER");
	line = ft_strjoinfree(usr, "@minishell ");
	line = ft_strjoinfree(line, pwd);
	line = ft_strjoinfree(line, "$ ");
	free(tmp);
	return (line);
}
