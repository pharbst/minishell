/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:24:41 by sschanga          #+#    #+#             */
/*   Updated: 2023/02/05 03:21:43 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	perror_msg(void)
{
	perror("Error");
	exit(1);
}

static char	*find_path(char **path)
{
	int		i;
	char	*get_path;

	i = 0;
	while (path[i] != NULL)
	{
		if (ft_strncmp("PATH=", path[i], 5) == 0)
		{
			get_path = ft_strdup(path[i] + 5);
			return (get_path);
		}
		i++;
	}
	return (NULL);
}

void	parse_argv(t_path *pipex, char **argv, char **envp)
{
	char	*set_path;

	pipex->infile = ft_strdup(argv[1]);
	if (!pipex->infile)
		perror_msg();
	pipex->cmds[0].cmd = ft_split(argv[2], ' ');
	if (!pipex->cmds[0].cmd)
		perror_msg();
	pipex->cmds[1].cmd = ft_split(argv[3], ' ');
	if (!pipex->cmds[1].cmd)
		perror_msg();
	pipex->outfile = ft_strdup(argv[4]);
	if (!pipex->outfile)
		perror_msg();
	set_path = find_path(envp);
	if (!set_path)
		perror_msg();
	pipex->path = ft_split(set_path, ':');
	free(set_path);
	if (!pipex->path)
		perror_msg();
}

void	set_pipe(t_path *pipex, char **envp)
{
	pid_t	pid;
	int		wstatus;

	pipe(pipex->fd);
	pid = fork();
	if (pid == -1)
		perror_msg();
	if (pid == 0)
		argv_child(pipex, envp);
	else
		argv_parent(pipex, envp);
	close(pipex->fd[0]);
	waitpid(pid, &wstatus, 0);
	close(pipex->fd[1]);
}

int	main(int argc, char **argv, char **envp)
{
	t_path	pipex;

	if (argc == 5)
	{
		set_null(&pipex);
		parse_argv(&pipex, argv, envp);
		set_pipe(&pipex, envp);
	}
	else
		printf("wrong command count!");
	return (0);
}
