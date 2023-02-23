/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 08:58:08 by ccompote          #+#    #+#             */
/*   Updated: 2023/02/23 18:25:03 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

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
        if (!ft_strncmp("PATH=", envp[i], 4))
		{
            res = ft_split(&envp[i][5], ':');
			// break ;
		}
        i++;
    }
    return (res);
}

void create_pipes(t_pipe *pipex)
{
	int i;

	i = 0;
	while (i < pipex->cmd_num - 1)
	{
		pipe(pipex->pipe_ends + 2 * i);
		i++;
	}
}

void init_pip(t_pipe *pipex, int argc, char **argv, char **envp)
{
	int i;
	//pipex->here_doc = ft_strncmp("here_doc", argv[1], 8); // 0 if there
	pipex->cmd_num = argc - 3;
	pipex->pipe_ends_num = 2 * (pipex->cmd_num - 1);
	pipex->pipe_ends = (int *)ft_calloc(pipex->pipe_ends_num, sizeof(int));
    pipex->splitted_path = find_path(envp);
	// if (!pipex->here_doc)
	// {
	// 	pipex->infile = open(argv[1], O_RDONLY);
	// 	pipex->outfile = open(argv[argc - 1], O_CREAT, O_RDWR, O_APPEND, 644);
	// }
	// else
	// {
		pipex->infile = open(argv[1], O_RDONLY);
		pipex->outfile = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	//}
	i = 0;
	while (i < pipex->cmd_num - 1)
	{
		pipe(pipex->pipe_ends + 2 * i);
		i++;
		
	}

}

// void here_doc(t_pipe *pipex, int argc, char **argv, char **envp)
// {
// 	int fd_doc;
// 	char *line;
	
// 	pipex->infile = open(argv[1], O_RDONLY);
// 	pipex->outfile = open(argv[argc - 1], O_CREAT, O_RDWR, O_APPEND, 644);
// 	fd_doc = open(".heredoc_tmp", O_RDONLY, O_TRUNC, O_CREAT, 644);
// 	ft_putstr_fd(">", 1);
// 	line = get_next_line(fd_doc);
// 	while (line && ft_strcmp(line, argv[2]))
// 	{
// 		write(fd_doc, line, ft_strlen(line));
// 		free(line);
// 	}
// 	close(fd_doc);
	// if (infile < 0)
	// {
	// 	unlink(".here_doc_tmp");
	// 	return(NULL);
	// }
// }

 int main(int argc, char **argv, char **envp)
 {
    t_pipe *pipex;

	pipex = malloc(sizeof(t_pipe));
	init_pip(pipex, argc, argv, envp);
	pipex->num_process = 0;
	while (pipex->num_process < pipex->cmd_num)
	{
		piping(pipex, argv, envp);
		pipex->num_process++;
	}
    // close_pipes();
    // i = -1;
    // while (++i < cmd_num)
    //     waitpid(-1, 0, NULL);
	// pipe_num = 2 * (cmd_num - 1);
	// pipex.cmd_num = argc - 3 - here_doc;
    // pipex.infile = open(argv[1], O_RDONLY);
    // pipex.argv = argv;
    //pipex.outfile = open(argv[argc - 1], O_CREAT, O_RDWR, O_TRUNC, 644); //truct если есть файл и в нем что-то напсано, он стирает и перезаписывает
    // close(pipex.pipe_fd[0]);
    // close(pipex.pipe_fd[1]);
    // waitpid(-1, 0, NULL);
    // waitpid(-1, 0, NULL);
    // free_parent();
    // close(pipex.infile);
    // close(pipex.outfile);
	return (0);
 }