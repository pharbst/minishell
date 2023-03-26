/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:46:23 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/26 06:02:40 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

void	get_token_location(t_token *token, int i, char *line)
{
	int	t_index;

	t_index = 0;
	while (t_index <= i)
	{
		token[t_index].location = &line[token[t_index].index];
		t_index++;
	}
}
