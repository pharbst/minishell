/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:54:55 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/15 05:30:48 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	syntax_check(bool read, bool value)
{
	static bool	syntax_error;

	if (read)
		return (syntax_error);
	else
		return (syntax_error = value, syntax_error);
}

void	ft_syntax_error(t_parsing *a)
{
	if (syntax_check(READ, NULL))
		return ;
	syntax_check(WRITE, true);
	a->exit_status = 1;
	if (a->token[a->token_index].type == NEW_LINE)
		printf("minishell: syntax error near unexpected token `newline'\n");
	else
		printf("minishell: syntax error near unexpected token `%c'\n",
			*a->token[a->token_index].location);
}
