/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 19:16:04 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/10 15:16:05 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	check_flag(char *argv)
{
	int	i;

	i = 1;
	if (*argv != '-')
		return (false);
	while (argv[i] == 'n')
		i++;
	if (argv[i] != '\0')
		return (false);
	return (true);
}

static void	print_args(int argc, char **argv, int i)
{
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i < argc - 1)
			printf(" ");
		i++;
	}
}

int	bi_echo(int argc, char **argv)
{
	int		i;
	bool	flag;

	if (argc == 1)
		return (printf("\n"), 0);
	i = 1;
	flag = false;
	while (check_flag(argv[i++]))
		flag = true;
	i--;
	print_args(argc, argv, i);
	if (!flag)
		printf("\n");
	return (0);
}
