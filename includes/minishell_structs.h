/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 01:58:02 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/28 16:19:52 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

typedef struct s_token
{
	int					type;
	char				*location;
}	t_token;

typedef struct s_redir_out
{
	int					fd_left;
	char				*file_right;
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

typedef struct s_pipex_common
{
	char				**paths;
	char				**envp;
	int					**pipes;
	int					number_nodes;
}	t_pipex_common;

typedef struct s_history
{
	struct s_pipex			*p_head;
	struct s_history		*next;
}	t_history;

typedef struct s_shell
{
	char				*user;
	char				*pwd;

	char				**argv;
	int					argc;
	char				**envp;

	// char				**history;
	char				*line;
	struct s_pipex		*p_head;
	// struct s_history	*h_head;
}	t_shell;

typedef struct s_parsing
{
	int					token_count;
	int					token_index;
	char				*line;
	t_token				*token;
	t_pipex				*pipex;
	char				**envp;
}	t_parsing;

#endif