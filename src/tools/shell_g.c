/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_g.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:37:17 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/26 05:41:55 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell_structs.h"

t_shell	*get_shell(bool read, t_shell *shell)
{
	static t_shell	*shell_g;

	if (read)
		return (shell_g);
	shell_g = shell;
	return (NULL);
}
