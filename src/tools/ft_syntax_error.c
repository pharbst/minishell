/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 22:54:55 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/26 09:44:02 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_tools.h"

bool	syntax_check(bool read, bool value)
{
	static bool	syntax_error;

	if (read)
		return (syntax_error);
	return (syntax_error = value, syntax_error);
}

void	ft_syntax_error(t_parsing *a)
{
	if (syntax_check(READ, NULL))
		return ;
	syntax_check(WRITE, true);
	a->exit_status = 2;
	if (a->token[a->token_index].type == NEW_LINE)
	{
		ft_putstrsfd(2, SHELL_NAME, SYNTAX_NL, NULL);
		a->exit_status = 2;
	}
	else
	{
		ft_putstrsfd(2, SHELL_NAME, SYNTAX_ERROR, NULL);
		ft_putchar_fd(*a->token[a->token_index].location, 2);
		ft_putstr_fd("'\n", 2);
	}
}
