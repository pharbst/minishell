/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_buildins.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 05:21:44 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/26 13:03:19 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BUILDINS_H
# define MINISHELL_BUILDINS_H

# include "libftio.h"
# include "minishell_structs.h"
# include "minishell_tools.h"

int		bi_cd(char **args, int argc, t_shell *shell);
int		bi_echo(int argc, char **argv);
int		print_env(char **env);
int		ft_exit(int argc, char **argv, t_shell *shell);

// export
void	print_line_with_quotes(char *line);
int		valid_var(char *argv);
int		var_new(char *env, char *name);
int		var_export(t_shell *shell, char **argv, int argc);

int		unset(t_shell *shell, char **argv);
char	*pwd(void);


#endif