/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:12:50 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/20 20:49:01 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	validate_fd(char *str)
{
	int	fd;

	fd = ft_atoi(str);
	if (fd <= 2 && fd >= 0)
		return (true);
	return (false);
}
