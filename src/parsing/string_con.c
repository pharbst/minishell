/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_con.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 14:08:01 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/14 22:08:22 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	string_condition(t_parsing *parameter, bool *cmd)
{
	if (parameter->token[*parameter->token_index + 1].type == STRING_CLOSE)
		*parameter->token_index += 2;		//\0 not handled
	//else
		//string exeption
	if (parameter->token[*parameter->token_index].type == SPACE || parameter->token[*parameter->token_index].type == PIPE || *parameter->token_index)
	{
		if (*cmd == false)
		{
			printf("cmd found\n");
			*cmd = true;
		}
		else
			printf("cmd argument or path found\n");
	}
	else if (parameter->token[*parameter->token_index].type == REDIRECT)
	{
		if (*parameter->token[*parameter->token_index].location == '<')
		
	}
}

//before > only filediscriptors without space are allowed everything else is an argument
