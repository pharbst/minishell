/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraysize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:55:53 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/26 05:35:16 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	get_arraysize(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
