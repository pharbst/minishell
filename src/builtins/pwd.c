/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:10:58 by pharbst           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/09 23:02:03 by pharbst          ###   ########.fr       */
=======
/*   Updated: 2023/03/09 22:30:03 by ccompote         ###   ########.fr       */
>>>>>>> ac9ca564dd5331c092c91aa32b18a2a8babf2c5e
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (0);
	return (pwd);
}
