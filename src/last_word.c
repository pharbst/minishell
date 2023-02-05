/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 03:02:32 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/05 06:28:50 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*last_word(char *str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
		i++;
	i--;
	while (ft_isalpha(str[i]))
		i--;
	i++;
	return (str + i);
}
