/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 01:58:02 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/05 06:43:33 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

typedef struct s_shell
{
	char	*user;
	char	*pwd;
	char	**argv;
	int		argc;
	char	**envp;
	char	**history;
	char	*line;
	// history
}	t_shell;

typedef struct s_pipex
{
	char			*cmd;
	char			*file_in;
	char			*file_out;
}	t_pipex;

#endif