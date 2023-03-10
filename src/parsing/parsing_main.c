/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 22:13:30 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/10 12:35:04 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tokenize(char *line, t_token *token, int i, int index)
{
	if (!line)
		return (0);
	while (line[index] && i < MAX_TOKENS)
	{
		token_dquote(token, &line[index], &i);
		token_squote(token, &line[index], &i);
		token_space(token, &line[index], &i, &index);
		token_dollar(token, &line[index], &i);
		token_redirect(token, &line[index], &i);
		token_pipe(token, &line[index], &i);
		token_string(token, &line[index], &i);
		index++;
	}
	if (i >= MAX_TOKENS)
		return (free(token), -1);
	return (i);
}

int	token_main(char *line, t_token *token)
{
	int	i;
	int	index;

	index = 0;
	i = 0;
	i = tokenize(line, token, i, index);
	if (i == -1)
		return (-1);
	while (open_quote(token, i) && i != -1)
	{
		line = strjoinfree(ft_strjoinchar(line, '\n'), readline("> "));
		if (ft_strlen(line) > 4095)
			return (-1);
		i = tokenize(line, token, i, index);
	}
	token[i].type = NEW_LINE;
	token[i].location = ft_strchr(line, '\0');
	return (i);
}

t_pipex	*parsing_condition(t_parsing *a)
{
	bool	cmd;
	t_pipex	*pipex;

	cmd = false;
	if (a->token_index >= a->token_count)
		return (NULL);
	pipex = ft_calloc(1, sizeof(t_pipex));
	if (!pipex)
		return (printf("Error: malloc failed in parsing condition\n"),free(pipex), NULL);
	while (a->token_index < a->token_count && a->token[a->token_index].type
		!= PIPE)
	{
		if (a->token[a->token_index].type == STRING_OPEN)
			string_condition(a, &cmd, pipex);
		else if (a->token[a->token_index].type == REDIRECT_IN)
			redirect_in_condition(a, pipex);
		else if (a->token[a->token_index].type == REDIRECT_OUT)
			redirect_out_condition(a, pipex, NULL);
		else if (a->token[a->token_index].type == DOLLAR)
			string_condition(a, &cmd, pipex);
		else if (a->token[a->token_index].type == DQUOTE_OPEN)
			string_condition(a, &cmd, pipex);
		else if (a->token[a->token_index].type == SQUOTE_OPEN)
			string_condition(a, &cmd, pipex);
		else if (a->token[a->token_index].type == SPACE_START)
			(a->token_index)++;
	}
	a->token_index += 1;
	return (pipex->next = parsing_condition(a), pipex);
}

t_pipex	*parsing(char *line, t_token *token, int token_count, char **envp)
{
	t_parsing	parameter;
	t_pipex		*pipex;

	parameter.token = token;
	parameter.token_count = token_count;
	parameter.token_index = 0;
	parameter.line = line;
	parameter.envp = envp;
	pipex = parsing_condition(&parameter);
	return (free(token), free(line), pipex);
}

t_pipex	*shell_parsing_main(char *line, char **envp)
{
	t_token	*token;
	int		token_count;

	if (ft_strlen(line) > 4095)
		return (NULL);
	token_count = 0;
	// line = ft_strftrim(line, &ft_isspace);
	if (!line)
		return (NULL);
	token = ft_calloc(2048, sizeof(t_token));
	token_count = token_main(line, token);
	// visual_token(token, token_count, line);
	if (token_count == -1 || token_count == 0)
		return (free(token), NULL);
	// visual_token(token, token_count, line);
	return (parsing(line, token, token_count, envp));
}
