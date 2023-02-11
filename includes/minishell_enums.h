/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_enums.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 07:32:39 by pharbst           #+#    #+#             */
/*   Updated: 2023/02/11 09:09:15 by pharbst          ###   ########.fr       */
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
# define SPACE -6
# define STRING -7
# define REDIRECT -8
# define DOLLAR -9
# define BRAKET_OPEN -10
# define BRAKET_CLOSE -11
# define ESCAPE -12

#endif