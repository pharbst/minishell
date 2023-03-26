/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_tools.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 04:04:34 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/26 05:50:09 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TOOLS_H
# define MINISHELL_TOOLS_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include "libftio.h"
# include "minishell_structs.h"
# include "minishell_error.h"
# include "minishell_enums.h"

int		get_arraysize(char **array);
int		error_code(int error_code, bool read);
int		find_var(char **envp_var, char *var_name);
char	*get_var_content(char **envp_var, char *var_name);
bool	syntax_check(bool read, bool value);
void	ft_syntax_error(t_parsing *a);
char	*grap(char *str, char **envp);
char	*last_word(char *str);

char	*get_prompt_line(t_shell *shell);
t_shell	*get_shell(bool read, t_shell *shell);
bool	signal_flag(bool read, bool set);
char	**split_free(char *line, char c);

void	visual_token(t_token *token, int token_count, char *line);
void	print_token_type(t_token token);

// print_pipex.c
void	print_arg(char **args);
void	print_redirection_out(t_redir_out *out);
void	print_pipex(t_pipex *p_head);

// shell_free.c
void	free_envp(char **envp);
void	free_red_out(t_redir_out *r_head);
void	free_pipex(t_shell *shell);

#endif