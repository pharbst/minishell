/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 01:58:02 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/07 02:09:31 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

typedef struct s_pipex
{
	char				*cmd;
	char				*file_in;
	char				*file_out;
	struct s_pipex		*next;
}	t_pipex;

typedef struct s_history
{
	struct s_pipex			*p_head;
	struct s_history		*next;
}	t_history;

typedef struct s_shell
{
	char		*user;
	char		*pwd;
	char		**argv;
	int			argc;
	char		**envp;
	char		**history;
	char		*line;
	struct s_pipex		*p_head;
	struct s_history	*h_head;
}	t_shell;

#endif