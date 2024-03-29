/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 01:58:02 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/29 19:40:25 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

# include <stdbool.h>
# include <signal.h>

typedef struct s_cd
{
	int		i;
	char	**old_pwd;
	char	**new_pwd;
	char	*n_pwd;
	char	*o_pwd;
	char	*str_dir;
}	t_cd;

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
	int					flag_builtin;
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