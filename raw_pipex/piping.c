/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:30:01 by ccompote          #+#    #+#             */
/*   Updated: 2023/02/23 18:27:05 by ccompote         ###   ########.fr       */
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

// void child1(t_pipe pipex)
// {
//     dub2(path.infile, 0);
//     //if dub < 0
//     dub2(path.pipe_fd[1], 1);
//     close(path.pipe_fd[0]);
//     command = make_cmd;
//     if (execve(command, command_2, path.envp) == -1)
//     {
//         perror("execve");
//         free_child;
//         exit(1);
//     }
// }

// void child2(t_pipe path)
// {
//     dub2(path.pipe_fd[0], 0);
//     dub2(1, path.outfile);
//     close(path.pipe_fd[1]);
// }

// int piping(t_pipe path)
// {
//     path.pid1 = fork();
    
//     if (path.pid1 == -1)
//         return (-1);
//     if (path.pid1 == 0)
//         child1(path);
//     waitpid(-1, NULL, 0);
//     path.pid2 = fork();
//     if (path.pid2 == 0)
//         child2(path);
// }

// //bonus
// my_dub2(zero, first)
//     dub2(zero, 0);
//     dub2(first, 1);

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

void piping(t_pipe *pipex, char **argv, char **envp)
{
    pid_t pid;
	char *command;

	pid = fork();
	if (pid == 0)
	{
        if (pipex->num_process == 0)
            //my_dub2(pipex->infile, pipe[1]);
		{
			dup2(pipex->infile, 0);
			dup2(pipex->pipe_ends[1], 1);
		}
        else if (pipex->num_process == pipex->cmd_num - 1)
            //my_dub2(pipex->pipe[2 * i - 2], pipex->outfile);
		{
			dup2(pipex->pipe_ends[2 * pipex->num_process - 2], 0);
			dup2(pipex->outfile, 1);
		}
        else  
		{
			dup2(pipex->pipe_ends[2 * pipex->num_process - 2], 0);
			dup2(pipex->pipe_ends[2 * pipex->num_process + 1], 1);
		}
		pipex->commands = ft_split(argv[2 + pipex->num_process], ' ');
		close_pipe_ends(pipex);
		command = (char *)make_cmd;
		printf("Hello\n");
		int i;
		i = 0;
		while (pipex->commands[i])
		{
			ft_putstr_fd(pipex->commands[i], 1);
			i++;
		}
    	if (execve(command, pipex->commands, envp) < 0)
		{
			printf("Fail\n");
		}
            //my_dub2(pipex->pipe[2 * i + 2], pipex->pipe[2 * i - 1]);
    }
    

    // while (i < cmd_num - 1)
    // {
    //     if (pipe(*pipe + 2 * i < 0))
    //         return (0);
    //     i++;
    // }
    // i = -1;
    // while (++i < cmd_num)
    // {
    //     child(pid, i); 
    // }
    // close_pipes();
    // i = -1;
    // while (++i < cmd_num)
    //     waitpid(-1, 0, NULL);
}

// 0 <- 1 2 <- 3 4 <- 5
// 0 -> 3
// 2 -> 5
