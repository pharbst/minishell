/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 22:13:30 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/26 06:23:49 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

int	tokenize(char *line, t_token *token, int i, int *index)
{
	if (!line)
		return (0);
	while (line[*index] && i < MAX_TOKENS)
	{
		token_dquote(token, &i, line, *index);
		token_squote(token, &i, line, *index);
		token_space(token, &i, line, index);
		token_dollar(token, &i, line, *index);
		token_redirect(token, &i, line, *index);
		token_pipe(token, &i, line, *index);
		token_string(token, &i, line, *index);
		*index += 1;
	}
	if (i >= MAX_TOKENS)
		return (free(token), -1);
	return (i);
}

int	token_main(char **line, t_token *token)
{
	int	i;
	int	index;

	index = 0;
	i = 0;
	i = tokenize(*line, token, i, &index);
	if (i == -1)
		return (-1);
	get_token_location(token, i, *line);
	if (i != -1 && i < MAX_TOKENS)
	{
		token[i].type = NEW_LINE;
		token[i].location = ft_strchr(*line, '\0');
	}
	else if (i >= MAX_TOKENS)
		return (free(token),
			printf("minishell: parsing error too many tokens\n"), -1);
	return (i);
}

t_pipex	*parsing_condition(t_parsing *a)
{
	bool	cmd;
	t_pipex	*pipex;

	cmd = false;
	pipex = ft_calloc(1, sizeof(t_pipex));
	while (a->token_index < a->token_count && a->token[a->token_index].type
		!= PIPE)
	{
		case_check(a, pipex, &cmd);
		if (a->abort)
			return (free(pipex), NULL);
	}
	pipex = post_check(a, pipex, cmd);
	if (!pipex)
		return (NULL);
	return (pipex->next = parsing_condition(a), pipex);
}

void	parsing(t_shell *shell, t_token *token, int token_count)
{
	t_parsing	parameter;

	parameter.token = token;
	parameter.token_count = token_count;
	parameter.token_index = 0;
	parameter.line = shell->line;
	parameter.envp = shell->envp;
	parameter.abort = false;
	parameter.exit_status = shell->exit_status;
	shell->p_head = parsing_condition(&parameter);
	shell->exit_status = parameter.exit_status;
	if (parameter.abort)
		return (free(shell->line),
			free_pipex(shell), shell->p_head = NULL, free(token));
	return (free(token), free(shell->line));
}

void	shell_parsing_main(t_shell *shell)
{
	t_token	*token;
	int		token_count;

	if (ft_strlen(shell->line) > 4095)
		return ;
	token_count = 0;
	if (!shell->line)
		return ;
	token = ft_calloc(2048, sizeof(t_token));
	token_count = token_main(&shell->line, token);
	if (token_count == -1 || token_count == 0)
		return (free(token));
	parsing(shell, token, token_count);
}
