/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 08:58:08 by ccompote          #+#    #+#             */
/*   Updated: 2023/02/26 14:32:53 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (NULL);
	while (i < len1)
		str[j++] = s1[i++];
	i = 0;
	while (i < len2)
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}


void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = malloc(count * size);
	if (!p)
		return (NULL);
	ft_bzero(p, size * count);
	return (p);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strncmp(char *s1,char *s2, int n)
{
	int			    i;
	unsigned char	*s11;
	unsigned char	*s22;

	s11 = (unsigned char *)s1;
	s22 = (unsigned char *)s2;
	i = 0;
	while (s11[i] != '\0' && s22[i] != '\0' && (i < n))
	{
		if (s11[i] != s22[i])
			return (s11[i] - s22[i]);
		i++;
	}
	if (i != n)
		return (s11[i] - s22[i]);
	return (0);
}

char **find_path(char **envp)
{
    int i;
    char **res;

    i = 0;
    res = NULL;
    while (envp[i])
    {
        if (!ft_strncmp("PATH", envp[i], 4))
		{
            res = ft_split(&envp[i][5], ':');
			break ;
		}
        i++;
    }
	if (!envp[i])
		return (NULL);
    return (res);
}

int *create_pipes()
{
	int i;

	i = 0;
	while (i < pipex->cmd_num - 1)
	{
		pipe(pipex->pipe_ends + 2 * i);
		i++;
	}
}

// void here_doc(char **argv)
// {
// 	int fd_doc;
// 	char *line;
// 	char *tmp;
	
// 	fd_doc = open("heredoc_tmp", O_WRONLY | O_TRUNC | O_CREAT, 0644);
// 	ft_putstr_fd(">", 1);
// 	line = get_next_line(0);
// 	tmp = ft_strjoin(argv[2], "\n");
// 	while (line && ft_strcmp(line, tmp))
// 	{
// 		ft_putstr_fd(line, fd_doc);
// 		free(line);
// 		ft_putstr_fd(">", 1);
// 		line = get_next_line(0);
// 	}
// 	free(line);
// 	close(fd_doc);
// }

void init_pip(t_pipe *pipex, int argc, char **argv, char **envp)
{
	int i;
	if (!ft_strncmp("here_doc", argv[1], 8))
		pipex->here_doc = 1;
	else
		pipex->here_doc = 0;
	pipex->cmd_num = argc - 3 - pipex->here_doc;
	pipex->pipe_ends_num = 2 * (pipex->cmd_num - 1);
	pipex->pipe_ends = (int *)ft_calloc(pipex->pipe_ends_num, sizeof(int));
    pipex->splitted_path = find_path(envp);
	if (pipex->here_doc)
	{
		here_doc(argv);
		pipex->infile = open("heredoc_tmp", O_RDONLY);
		pipex->outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else
	{
		pipex->infile = open(argv[1], O_RDONLY);
		pipex->outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	i = 0;
	while (i < pipex->cmd_num - 1)
	{
		if (pipe(pipex->pipe_ends + 2 * i) < 0)
			printf("Pipe failed\n");
		i++;
	}

// }


 int pipex(t_pipex *p_head, char **envp)
 {
    t_pipe *pipex;

	pipex = malloc(sizeof(t_pipe));
	init_pip(pipex, argc, argv, envp);
	pipex->num_process = 0;
	pipex->pid = 0;
	pipex->commands = NULL;
	while (pipex->num_process < pipex->cmd_num)
	{
		piping(pipex, argv, envp);
		pipex->num_process++;
	}
	close(pipex->infile);
	close(pipex->outfile);
	close_pipe_ends(pipex);
	waitpid(-1, NULL, 0);
	int i = 0;
    while (i < pipex->cmd_num)
	{
        waitpid(-1, NULL, 0);
		i++;
	}
	if (pipex->here_doc)
		unlink("heredoc_tmp");
 }