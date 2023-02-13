/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_functions.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 01:55:03 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/13 11:22:56 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FUNCTIONS_H
# define MINISHELL_FUNCTIONS_H

# include "minishell.h"

void			ft_exit(t_shell *shell);
void			ft_shell(t_shell *shell);
t_pipex			*shell_parsing_main(char *line);
//tokenize
int				tokenize(char *line, t_token *token, int i);
bool			open_quote(t_token *token, int i);
bool			open_squote(t_token *token, int i);
bool			open_dquote(t_token *token, int i);
bool			open_string(t_token *token, int i);
void			token_dquote(t_token *token, char *line, int *i);
void			token_squote(t_token *token, char *line, int *i);
void			token_space(t_token *token, char *line, int *i, int *index);
void			token_escape(t_token *token, char *line, int *i);
void			token_dollar(t_token *token, char *line, int *i);
void			token_braket(t_token *token, char *line, int *i);
void			token_redirect(t_token *token, char *line, int *i);
void			token_pipe(t_token *token, char *line, int *i);
void			token_string(t_token *token, char *line, int *i);
//tools
char			*grap(char *str, char **envp);
char			*last_word(char *str);
void			prompt_line(t_shell *shell);

// pipe functions
#endif