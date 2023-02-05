/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_functions.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 01:55:03 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/05 04:48:09 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FUNCTIONS_H
# define MINISHELL_FUNCTIONS_H

# include "minishell_structs.h"

// string manipulation
char	*grap(char *key, char **envp);
char	*last_word(char *str);

// minishell functions
void	print_env(char **envp);
void	prompt_line(t_shell *shell);

// pipe functions
#endif