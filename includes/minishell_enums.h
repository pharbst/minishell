/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_enums.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 07:32:39 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/09 22:36:40 by pharbst          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ENUMS_H
# define MINISHELL_ENUMS_H

//Token types
# define DQUOTE_OPEN -1
# define DQUOTE_CLOSE -2
# define SQUOTE_OPEN -3
# define SQUOTE_CLOSE -4
# define PIPE -5
# define SPACE_START -6
# define STRING_OPEN -7
# define REDIRECT_OUT -8
# define DOLLAR -9
# define STRING_CLOSE -13
# define REDIRECT_IN -14
# define NEWLINE -15
# define MAX_TOKENS 2048

# define READ 1
# define WRITE 0

#endif