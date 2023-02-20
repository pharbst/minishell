/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:03:36 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/20 15:29:52 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_type(t_token token)
{
	if (token.type == DQUOTE_OPEN)
		printf("DQUOTE_OPEN\n");
	if (token.type == DQUOTE_CLOSE)
		printf("DQUOTE_CLOSE\n");
	if (token.type == SQUOTE_OPEN)
		printf("SQUOTE_OPEN\n");
	if (token.type == SQUOTE_CLOSE)
		printf("SQUOTE_CLOSE\n");
	if (token.type == PIPE)
		printf("PIPE\n");
	if (token.type == REDIRECT_IN)
		printf("REDIRECT_IN\n");
	if (token.type == REDIRECT_OUT)
		printf("REDIRECT_OUT\n");
	if (token.type == STRING_OPEN)
		printf("STRING_OPEN\n");
	if (token.type == STRING_CLOSE)
		printf("STRING_CLOSE\n");
	if (token.type == DOLLAR)
		printf("DOLLAR\n");
	if (token.type == SPACE_START)
		printf("SPACE_START\n");
}

void	visual_token(t_token *token, int token_count, char *line)
{
	int	i;

	i = 0;
	while (i < token_count)
	{
		printf("%s\n", line);
		for (int tmp = token[i].location - line; tmp > 0; tmp--)
			printf(" ");
		printf("^\n");
		for (int tmp = token[i].location - line; tmp > 0; tmp--)
			printf(" ");
		print_token_type(token[i]);
		printf("\n\n\n");
		i++;
	}
}	
