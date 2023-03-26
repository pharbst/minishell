/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_code.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 22:20:44 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/26 05:35:48 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

int	error_code(int error_code, bool read)
{
	static int	code;

	if (read)
		return (code);
	code = error_code;
	return (0);
}
