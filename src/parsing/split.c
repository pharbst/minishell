/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 21:59:47 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/07 02:22:27 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_pipex	*save_cmd(char *line, int j, int i, int k)
{
	t_pipex	*pipex;

	pipex = ft_calloc(sizeof(t_pipex), 1);
	pipex->cmd = ft_substr(line, j, i + k + 1);
	return (pipex);
}

static void	get_redir(char *line, int j, t_pipex *pipex)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (line[j] == '<')
	{
		j++;
		while (ft_strchr("\t\r\v\f ", line[j]))
			j++;
		while (!ft_strchr("|>", line[j + i]))
			i++;
		k--;
		while (ft_strchr("\t\r\v\f ", line[j + i + k]))
			k--;
		pipex->file_in = ft_substr(line, j, i + k + 1);
		printf("file_in: %s\n", pipex->file_in);
	}
	j = j + i;
	if (line[j] == '>')
	{
		j++;
		while (ft_strchr("\t\r\v\f ", line[j]))
			j++;
		while (line[j + i] != '|' && line[j + i] != '\0')
			i++;
		k--;
		while (ft_strchr("\t\r\v\f ", line[j + i + k]))
			k--;
		pipex->file_out = ft_substr(line, j, i + k + 1);
		printf("file_out: %s\n", pipex->file_out);
	}
	j = j + i;
	if (line[j] == '<')
	{
		j++;
		while (ft_strchr("\t\r\v\f ", line[j]))
			j++;
		while (!ft_strchr("|>", line[j + i]))
			i++;
		k--;
		while (ft_strchr("\t\r\v\f ", line[j + i + k]))
			k--;
		pipex->file_in = ft_substr(line, j, i + k);
		printf("file_in: %s\n", pipex->file_in);
	}
}

t_pipex	*shell_split(char *line)
{
	t_pipex	*pipex;
	t_pipex	*tmp;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	tmp = NULL;
	while (ft_strchr("\t\r\v\f ", line[j]))
		j++;
	if (line[j] == '\0')
		return (NULL);
	while (!ft_strchr("|<>", line[j + i]))
		if (line[j + i++] == '"')
			while (line[j + i] != '"' && line[j + i] != '\0')
				i++;
	k--;
	while (ft_strchr("\t\r\v\f ", line[j + i + k]))
		k--;
	pipex = save_cmd(line, j, i, k);
	printf("cmd: %s\n", pipex->cmd);
	if (line[j + i] == '<' || line[j + i] == '>')
		get_redir(line, j + i, pipex);
	if (line[j + i] == '|')
		pipex->next = shell_split(ft_substr(line, j + i + 1, ft_strlen(line)));
	return (pipex);
}
