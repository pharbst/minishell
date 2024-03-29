/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 01:55:03 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/26 06:13:44 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell_structs.h"
# include "minishell_buildins.h"
# include "minishell_error.h"
# include "minishell_tools.h"
# include "minishell_parsing.h"

//main
void			shell_interactive(t_shell *shell);

#endif