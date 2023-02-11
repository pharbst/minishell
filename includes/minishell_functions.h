/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_functions.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 01:55:03 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/11 12:57:06 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_FUNCTIONS_H
# define MINISHELL_FUNCTIONS_H

# include "minishell.h"

void	ft_exit(t_shell *shell);
void	ft_shell(t_shell *shell);
void	prompt_line(t_shell *shell);
t_pipex	*shell_parsing_main(char *line);
unsigned int	tokenize(char *line, t_token *token, unsigned int i);
bool	open_quote(t_token *token, unsigned int i);
bool	open_squote(t_token *token, unsigned int i);
bool	open_dquote(t_token *token, unsigned int i);
void	token_dquote(t_token *token, char *line, unsigned int *i, unsigned int *dquote);
void	token_squote(t_token *token, char *line, unsigned int *i, unsigned int *squote);
void	token_space(t_token *token, char *line, unsigned int *i, int *index);
void	token_escape(t_token *token, char *line, unsigned int *i);
void	token_dollar(t_token *token, char *line, unsigned int *i);
void	token_braket(t_token *token, char *line, unsigned int *i);
void	token_redirect(t_token *token, char *line, unsigned int *i);
void	token_pipe(t_token *token, char *line, unsigned int *i);
char	*grap(char *str, char **envp);
char	*last_word(char *str);

// pipe functions
#endif