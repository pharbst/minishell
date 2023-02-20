/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 01:48:44 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/20 12:43:22 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt_line(t_shell *shell)
{
	char	*line;
	
	line = ft_strjoin(last_word(grap("USER", shell->envp)), "@minishell ");
	line = ft_strjoinfree(line, last_word(grap("PWD", shell->envp)));
	line = ft_strjoinfree(line, "$ ");
	return (line);
	// ft_printf("%s@minishell %s %% ", last_word(grap("USER", shell->envp)), last_word(grap("PWD", shell->envp)));
}