/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:43:59 by ccompote          #+#    #+#             */
/*   Updated: 2023/03/09 20:30:10 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_free(char *line, char c)
{
	char	**ret;

	ret = ft_split(line, c);
	printf("");
	return (free(line), ret);
}
