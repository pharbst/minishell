/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:33:02 by ccompote          #+#    #+#             */
/*   Updated: 2023/02/26 17:11:24 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pipex_strjoin(char *s1, char *s2)
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

char *get_cmd(t_pipex *p_head, char **paths)
{
	int i;
    char *tmp;
    char *command;
    
	i = 0;
    while (paths[i])
    {
        tmp = ft_pipex_strjoin(paths[i], "/");
		if (!tmp)
			printf("tmp failed\n");
        command = ft_pipex_strjoin(tmp, p_head->cmd);
        free(tmp);
		if (!access(command, 0))
			return (command);
		free(command);
        i++;
    }
    return (NULL);
}

char *make_cmd(t_pipex *p_head, char **paths)
{
	// check absolute path
	if (!access(p_head->cmd, 0))
		return (p_head->cmd);
	return (get_cmd(p_head, paths));
}

int	ft_words(const char *str, char c)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			k++;
			while (str[i] != '\0' && str[i] != c)
				i++;
		}
	}
	return (k);
}

char	**free_words(int i, char **ptr)
{
	while (i > 0)
	{
		free(ptr[i - 1]);
		i--;
	}
	free(ptr);
	return (NULL);
}

char	*ft_wd(const char *str, char c)
{
	int		i;
	char	*wd;

	i = 0;
	while (*str && *str == c)
		str++;
	while (str[i] && str[i] != c)
		i++;
	wd = (char *)malloc(sizeof(char) * (i + 1));
	if (wd == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		wd[i] = str[i];
		i++;
	}
	wd[i] = '\0';
	return (wd);
}

char	**ft_pipex_split(char *s, char c)
{
	char	**ptr_words;
	int		words;
	int		i;

	if (!s)
		return (NULL);
	words = ft_words(s, c);
	ptr_words = malloc(sizeof(char *) * (words + 1));
	if (ptr_words == NULL)
		return (NULL);
	i = 0;
	while (i < words)
	{
		while (*s && *s == c)
			s++;
		ptr_words[i] = ft_wd(s, c);
		if (ptr_words[i] == NULL)
			return (free_words(i, ptr_words));
		while (*s && *s != c)
			s++;
		i++;
	}
	ptr_words[i] = NULL;
	return (ptr_words);
}

int	ft_pipex_strncmp(char *s1,char *s2, int n)
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
        if (!ft_pipex_strncmp("PATH", envp[i], 4))
		{
            res = ft_pipex_split(&envp[i][5], ':');
			break ;
		}
        i++;
    }
	if (!envp[i])
		return (NULL);
    return (res);
}

void close_pipes(int **pipes, int cur, int number_nodes)
{
	int	i;
	int len;

	len = number_nodes - 1;
	i = 0;
	if (cur == 0)
		close(pipes[0][0]);
	else if (cur == len)
		close(pipes[len - 1][1]);
	else
	{
		close(pipes[cur - 1][1]);
		close(pipes[cur][0]);
	}
	while (pipes[i])
	{
		if (cur < i || cur > i + 1)
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		i++;
	}
}

int count_nodes(t_pipex *p_head)
{
	int i;

	i = 0;
	while (p_head)
	{
		p_head = p_head->next;
		i++;
	}
	return (i);
}

void piping(t_pipex *p_head, char **paths, char **envp, int process, int **pipes, int number_nodes)
{
	pid_t pid;
	int fd_outfile;
	int fd_infile;
	int i;
	char **commands;
	char *command;

	i = 0;
	while (p_head->args[i])
		i++;
	pid = fork();
	if (pid == 0)
	{
		if (process == 0)
		{
			if (p_head->in)
			{
				fd_infile = open(p_head->in, O_RDONLY);
				dup2(fd_infile, STDIN_FILENO);
				close(fd_infile);
			}
			if (p_head->next)
				dup2(pipes[0][1], STDOUT_FILENO);
			else
			{
				if (p_head->out)
				{
					fd_outfile = open(p_head->out->file_right, O_CREAT | O_WRONLY | O_TRUNC, 0644);
					dup2(fd_outfile, 1);
					close(fd_outfile);
				}
			}
		}
		else if (process == number_nodes - 1)
		{
			if (p_head->out)
			{
				fd_outfile = open(p_head->out->file_right, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				dup2(fd_outfile, STDOUT_FILENO);
				close(fd_outfile);
			}
			dup2(pipes[process - 1][0], STDIN_FILENO);
		}
		else
		{
			dup2(pipes[process - 1][0], STDIN_FILENO);
			dup2(pipes[process][1], STDOUT_FILENO);
		}
		if (number_nodes > 1)
		{
			close_pipes(pipes, process, number_nodes);
		}
		commands = malloc(sizeof(char *) * (i + 1));
		commands[i] = NULL;
		i--;
		while (i >= 0)
		{
			commands[i] = p_head->args[i];
			i--;
		}
		command = make_cmd(p_head, paths);
		execve(command, commands, envp);
    }
}

void execute(t_pipex *p_head, char **envp)
{
	char **paths;
	int number_nodes;
	int **pipes;
	int i;
	
	i = 0;
	number_nodes = count_nodes(p_head);
	pipes = malloc(sizeof(int *) * number_nodes + 1);
	paths = find_path(envp);
	while (i < number_nodes - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		pipe(pipes[i]);
		i++;
	}
	pipes[i] = NULL;
	i = 0;
	while (i < number_nodes)
	{
		piping(p_head, paths, envp, i, pipes, number_nodes);
		p_head = p_head->next;
		i++;
	}
	i = 0;
	while (pipes[i])
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < number_nodes)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}
