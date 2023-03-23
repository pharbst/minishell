/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 01:58:02 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/23 09:31:42 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

typedef struct s_token
{
	int					type;
	char				*location;
	int					index;
}	t_token;

typedef struct s_redir_out
{
	int					fd_left;
	char				*file_right;
	int					fd_right;
	bool				append;
	struct s_redir_out	*next;
}	t_redir_out;

typedef struct s_pipex
{
	char				*cmd;
	char				**args;
	char				*in;
	int					fd_in;
	struct s_redir_out	*out;
	struct s_pipex		*next;
}	t_pipex;

typedef struct s_parsing
{
	int					token_count;
	int					token_index;
	int					exit_status;
	bool				abort;
	char				*line;
	t_token				*token;
	t_pipex				*pipex;
	char				**envp;
}	t_parsing;

typedef struct s_pipex_common
{
	char				**paths;
	int					**pipes;
	int					error_code;
	int					number_nodes;
	int					argc;
	int					*pids;
}	t_pipex_common;

typedef struct s_shell
{
	char				*user;
	char				*pwd;
	int					exit_status;

	char				**argv;
	int					argc;
	char				**envp;
	char				**envp_exported;

	char				*line;
	struct s_pipex		*p_head;
}	t_shell;

typedef struct s_shell_rl
{
	char				*promt;
	char				*tmp;
	char				buff;
	struct sigaction	sa;
	int					pipe_fd[2][2];
	int					pid;
	int					status;
}	t_shell_rl;

#endif