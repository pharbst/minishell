/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:12:50 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/19 15:13:57 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	validate_fd(char *str)
{
	int	fd;

	printf("enter validate_fd\n");
	fd = ft_atoi(str);
	if (fd <= 2 && fd >= 0)
		return (true);
	return (false);
}
