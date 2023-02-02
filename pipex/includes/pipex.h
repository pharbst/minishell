/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:25:24 by sschanga          #+#    #+#             */
/*   Updated: 2023/02/02 06:45:54 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libftio.h"
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>

typedef struct s_cmd
{
	char	**cmd;
	char	*cmd_argv;
}	t_cmd;

typedef struct s_path
{
	int		fd[2];
	t_cmd	cmds[2];
	t_cmd	cmd_path[2];
	char	**path;
	char	*infile;
	char	*outfile;
	int		infile_fd;
	int		outfile_fd;
}	t_path;

//Pipex
void		parse_argv(t_path *pipex, char **argv, char **envp);
void		set_pipe(t_path *pipex, char **envp);
void		argv_child(t_path *pipex, char **envp);
void		argv_parent(t_path *pipex, char **envp);
//Protect
void		set_null(t_path *pipex);
void		perror_msg(void);
#endif
