/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 22:23:01 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/26 17:36:00 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ERROR_H
# define MINISHELL_ERROR_H

# define SHELL_NAME "minishell: "
# define SYNTAX_RL_EOF "unexpected EOF while looking for matching `\"'\n"
# define SYNTAX_EOF "syntax error: unexpected end of file\n"
# define SYNTAX_NL "syntax error near unexpected token `newline'\n"
# define NO_SUCH_FILE ": No such file or directory\n"
# define VAR_NO_VALID "': not a valid identifier\n"
# define NO_COMMAND ": command not found\n"
# define NO_PERM ": Permission denied\n"
# define EXIT_WRONG_ARG ": numeric argument required\n"
# define EXIT_TOO_MANY_ARGS "exit: too many arguments\n"
# define SYNTAX_ERROR "syntax error near unexpected token `"

#endif