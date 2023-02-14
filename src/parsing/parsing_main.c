/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 22:13:30 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/14 22:10:25 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize(char *line, t_token *token, int i)
{
	static int		index;

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

	i = 0;
	i = tokenize(line, token, i);
	if (i == -1)
		return (-1);
	while (open_quote(token, i) && i != -1)
	{
		line = ft_strjoinfree(ft_strjoinchar(line, '\n'), readline("> "));
		if (ft_strlen(line) > 4095)
			return (-1);
		i = tokenize(line, token, i);
	}
	return (i);
}

t_pipex	*parsing_condition(t_parsing *parameter)
{
	bool	cmd;

	cmd = false;
	parameter->pipex = ft_calloc(1, sizeof(t_pipex));
	if (!parameter->pipex)
		return (NULL);
	while (parameter->token[*parameter->token_index].type != PIPE && *parameter->token_index <= parameter->token_count)
	{
		if (parameter->token[*parameter->token_index].type == STRING_OPEN)
			string_condition(parameter, &cmd);
		if (parameter->token[*parameter->token_index].type == REDIRECT)
			redirect_condition(parameter);
		if (parameter->token[*parameter->token_index].type == DOLLAR)
			dollar_condition(parameter);
		if (parameter->token[*parameter->token_index].type == DQUOTE_OPEN)
			dquote_condition(parameter);
		if (parameter->token[*parameter->token_index].type == SQUOTE_OPEN)
			squote_condition(parameter);
		if (parameter->token[*parameter->token_index].type == PIPE)
			break ;
		if (parameter->token[*parameter->token_index].type == SPACE)
			(*parameter->token_index)++;
	}
}

t_pipex	*parsing(char *line, t_token *token, int token_count)
{
	t_parsing	parameter;
	static int	token_index;

	if (token_index >= token_count)
		return (NULL);
	parameter.token = token;
	parameter.token_count = token_count;
	parameter.token_index = &token_index;
	parameter.line = line;
	parameter.pipex = parsing_condition(&parameter);
	return (parameter.pipex->next = parsing(line, token, token_count), parameter.pipex);
}

t_pipex	*shell_parsing_main(char *line)
{
	t_token	*token;
	int		token_count;

	if (ft_strlen(line) > 4095)
		return (NULL);
	token_count = 0;
	line = ft_strftrim(line, &ft_isspace);
	if (!line)
		return (NULL);
	token = ft_calloc(2048, sizeof(t_token));
	token_count = token_main(line, token);
	if (token_count == -1 || token_count == 0)
		return (free(token), NULL);
	return (parsing(line, token, token_count));
}
