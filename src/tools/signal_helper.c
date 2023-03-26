/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:03:27 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/26 05:42:28 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	signal_flag(bool read, bool set)
{
	static bool	flag;

	if (read)
		return (flag);
	else
		flag = set;
	return (set);
}
