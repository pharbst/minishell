/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraysize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:55:53 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/22 16:01:21 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_arraysize(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
