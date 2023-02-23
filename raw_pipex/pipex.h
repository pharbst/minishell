/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:05:30 by ccompote          #+#    #+#             */
/*   Updated: 2023/02/23 18:16:38 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
# define PIPEX_H

#include <stdlib.h>
#include <unistd.h>
# include <fcntl.h>
# include "get_next_line.h"
# include <stdio.h>

typedef struct s_pipe
{
    char **splitted_path;
    pid_t pid1;
    pid_t pid2;
    int infile;
    int outfile;
    int here_doc;
    int cmd_num;
	int *pipe_ends;
	int pipe_ends_num;
	char **commands;
	int	num_process;
    
} t_pipe;

char	**ft_split(char *s, char c);
void 	piping(t_pipe *pipex, char **argv, char **envp);
char	*ft_strjoin(char *s1, char *s2);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);

#endif