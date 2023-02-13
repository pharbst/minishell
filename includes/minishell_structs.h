/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 01:58:02 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/13 06:20:16 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

typedef struct s_token
{
	int					type;
	char				*location;
}	t_token;

typedef struct s_redir_in
{
	char				*file;
	struct s_redir_in	*next;
}	t_redir_in;

typedef struct s_redir_out
{
	char				*file;
	struct s_redir_out	*next;
}	t_redir_out;

typedef struct s_pipex
{
	char				*cmd;
	char				**args;
	struct s_redir_in	*in;
	struct s_redir_out	*out;
	struct s_pipex		*next;
}	t_pipex;

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
	char				**history;
	char				*line;
	struct s_pipex		*p_head;
	struct s_history	*h_head;
}	t_shell;

#endif