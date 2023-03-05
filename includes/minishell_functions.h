/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_functions.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 01:55:03 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/05 16:02:32 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_FUNCTIONS_H
# define MINISHELL_FUNCTIONS_H

# include "minishell.h"

//main
void			shell_interactive(t_shell *shell);
void			shell_alone(t_shell *shell);

//tokenize
int				tokenize(char *line, t_token *token, int i, int index);
bool			open_quote(t_token *token, int i);
bool			open_squote(t_token *token, int i);
bool			open_dquote(t_token *token, int i);
bool			open_string(t_token *token, int i);
void			token_dquote(t_token *token, char *line, int *i);
void			token_squote(t_token *token, char *line, int *i);
void			token_space(t_token *token, char *line, int *i, int *index);
void			token_dollar(t_token *token, char *line, int *i);
void			token_redirect(t_token *token, char *line, int *i);
void			token_pipe(t_token *token, char *line, int *i);
void			token_string(t_token *token, char *line, int *i);

//parsing
t_pipex			*shell_parsing_main(char *line, char **envp);
void			string_condition(t_parsing *a, bool *cmd, t_pipex *pipex);
char			*quote_expand(t_parsing *a);
char			*get_var(char *var, char **envp);
bool			validate_fd(char *str);
char			**join_arg(t_pipex *pipex, char *tmp);
void			redirect_out_condition(t_parsing *a, t_pipex *pipex,
					char *file1);
void			redirect_in_condition(t_parsing *a, t_pipex *pipex);
char			*str_cat(t_parsing *a);
void			hdc(t_parsing *a, t_pipex *pipex);

// pipe functions
int				execute(t_shell *shell);
int				get_info_for_pipex(t_pipex_common *pipex_info, t_pipex *p_head, char **envp);
void			piping(t_pipex *p_head, t_pipex_common *pipex_info, int process, t_shell *shell);
void			close_pipes(int **pipes, int cur, int number_nodes);


//buildins
int				bi_echo(int argc, char **argv);
int				print_env(char **env);
char			**var_export(char **envp, char **argv, int argc);
int				pwd(void);
void			unset(char *var_name, char **env);
int				bi_cd(char **args, int argc, char **envp);

// exit
void			ft_exit(t_shell *shell);
void			free_pipex(t_pipex *p_head);
void			free_red_out(t_redir_out *r_head);
void			free_envp(char **envp);

//tools
char			*grap(char *str, char **envp);
char			*last_word(char *str);
char			*get_prompt_line(t_shell *shell);
char			*strjoinfree(char *s1, char *s2);
void			visual_token(t_token *token, int token_count, char *line);
void			print_token_type(t_token token);
void			print_pipex(t_pipex *p_head);
void			print_arg(char **args);
t_shell			*get_shell(bool read, t_shell *shell);
int				get_arraysize(char **array);
int				find_var(char **envp_var, char *var_name);
char			*get_var_content(char **envp_var, char *var_name);
int				error_code(int error_code, bool read);
char			**split_free(char *line, char c);


#endif