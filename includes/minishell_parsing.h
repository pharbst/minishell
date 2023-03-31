/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 03:47:11 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/31 08:09:51 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

# include <stdio.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "minishell_structs.h"
# include "minishell_error.h"
# include "minishell_tools.h"
# include "minishell_enums.h"
# include "minishell_buildins.h"
# include "libftio.h"

# define COLOR_SET_1 "\001\033[1;34m\002@\001\033[1;32m\002m\001\033[1;33m\002i\001\033[1;35m\002n"
# define COLOR_SET_2 "\001\033[1;36m\002i\001\033[1;34m\002s\001\033[1;31m\002hell \001\033[0;33m\002"

// check_open.c
bool	open_quote(t_token *token, int i);
bool	open_squote(t_token *token, int i);
bool	open_dquote(t_token *token, int i);
bool	open_string(t_token *token, int i);

// here_doc_condition.c
bool	hdc_syntax_check(t_parsing *a);
char	*get_delimiter(t_parsing *a);
void	hdc_child(char *delimiter, int pfd[2]);
void	exec_hdc(char *delimiter, int pfd[2], t_parsing *a);
void	hdc(t_parsing *a, t_pipex *pipex);

// here_doc_delimiter.c
char	*hdc_dollar(t_parsing *a);
char	*hdc_string(t_parsing *a);
char	*hdc_dquote(t_parsing *a);
char	*hdc_squote(t_parsing *a);

// here_doc_interpret.c
void	hdc_interpreter(int fd, t_pipex *pipex);
void	hdc_mid(char *line, char **new_line, t_shell *shell);
char	*hdc_inter_dollar(char *line, int *index, t_shell *shell);

// join_arg.c
char	**join_arg(t_pipex *pipex, char *tmp);

// parsing_helper.c
t_pipex	*post_check(t_parsing *a, t_pipex *pipex, bool cmd);
void	case_check(t_parsing *a, t_pipex *pipex, bool *cmd);

// parsing_main.c
int		tokenize(char *line, t_token *token, int i, int *index);
int		token_main(char **line, t_token *token);
t_pipex	*parsing_condition(t_parsing *a);
void	parsing(t_shell *shell, t_token *token, int token_count);
void	shell_parsing_main(t_shell *shell);

// quote_expand.c
char	*expand_dollar_var(t_parsing *a);
char	*dquote_expand(t_parsing *a);
char	*squote_expand(t_parsing *a);

// redirect_condition.c
void	redirect_in_condition(t_parsing *a, t_pipex *pipex);
void	redirect(t_parsing *a, t_redir_out *new);
void	redirect_out_condition(t_parsing *a, t_pipex *pipex, char *file1);

// redirect_helper.c
void	add_redir_out(t_pipex *pipex, t_redir_out *new);
bool	red_helper(t_parsing *a, t_redir_out *new);
bool	red_helper2(t_parsing *a, t_redir_out *new);

// shell_readline_helpe.c
void	shell_rloq_parent(t_shell *shell, t_shell_rl *rl);
void	shell_rl_helper(t_shell *shell, t_shell_rl *rl);
void	shell_rl_exit(t_shell *shell);

// shell_readline.c
char	*get_prompt_line(t_shell *shell);
bool	openquote(char *line);
void	shell_rliq(t_shell_rl rl, char **line);
void	shell_rloq(t_shell_rl rl);
void	shell_readline(t_shell *shell);

// str_cat.c
char	*dollar_helper(t_parsing *a, char *tmp);
char	*str_cat_helper(t_parsing *a, char *tmp);
char	*str_cat(t_parsing *a);

// string_con.c
void	string_condition(t_parsing *a, bool *cmd, t_pipex *pipex);

// token_helper_tokencheck_quote.c
void	token_dquote(t_token *token, int *i, char *line, int index);
void	token_squote(t_token *token, int *i, char *line, int index);

// token_helper_tokencheck.c
void	token_space(t_token *token, int *i, char *line, int *index);
void	token_pipe(t_token *token, int *i, char *line, int index);
void	token_redirect(t_token *token, int *i, char *line, int index);
void	token_dollar(t_token *token, int *i, char *line, int index);
void	token_string(t_token *token, int *i, char *line, int index);

// token_helper.c
void	get_token_location(t_token *token, int i, char *line);

// validate_fd.c
bool	validate_fd(char *str);

#endif