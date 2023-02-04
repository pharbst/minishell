/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 06:27:24 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/04 02:03:39 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv)
{
	t_shell shell;

	shell.user = "Peter";
	shell.pwd = "home/peter";
	if (!argc || !argv)
		return (1);
	prompt_line(&shell);
	return (0);
}