/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:30:01 by ccompote          #+#    #+#             */
/*   Updated: 2023/02/26 13:26:17 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char *get_cmd(t_pipe *pipex)
{
	int i;
    char *tmp;
    char *command;
    
	i = 0;
    while (pipex->splitted_path[i])
    {
        tmp = ft_strjoin(pipex->splitted_path[i], "/");
		if (!tmp)
			printf("tmp failed\n");
        command = ft_strjoin(tmp, pipex->commands[0]);
        free(tmp);
		if (!access(command, 0))
			return (command);
		free(command);
        i++;
    }
    return (NULL);
}

char *make_cmd(t_pipe *pipex)
{
	// проверить если абсолютный путь
	if (!access(pipex->commands[0], 0))
		return (pipex->commands[0]);
	return (get_cmd(pipex));
}

void close_pipe_ends(t_pipe *pipex)
{
	int i;

	i = 0;
	while(i < pipex->pipe_ends_num)
	{
		close(pipex->pipe_ends[i]);
		i++;
	}
}

void piping(t_pipex *p_head, int *fd_pipes, char **envp, int process, char **paths)
{
	char *command;
	pid_t pid;

	pid = fork();
	int fd_infile;
	if (pid == 0)
	{
        if (pipex->num_process == 0)
		{
			dup2(pipex->infile, 0);
			dup2(pipex->pipe_ends[1], 1);
		}
        else if (pipex->num_process == pipex->cmd_num - 1)
		{
			dup2(pipex->pipe_ends[2 * pipex->num_process - 2], 0);
			dup2(pipex->outfile, 1);
		}
        else  
		{
			dup2(pipex->pipe_ends[2 * pipex->num_process - 2], 0);
			dup2(pipex->pipe_ends[2 * pipex->num_process + 1], 1);
		}
		close_pipe_ends(pipex);
		pipex->commands = ft_split(argv[2 + pipex->num_process + pipex->here_doc], ' ');
		command = make_cmd(pipex);
    	if (execve(command, pipex->commands, envp) < 0)
		{
			printf("Fail\n");
		}
}