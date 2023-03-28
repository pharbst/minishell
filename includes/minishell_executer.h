/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executer.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 05:28:22 by pharbst           #+#    #+#             */
/*   Updated: 2023/03/28 21:48:48 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXECUTER_H
# define MINISHELL_EXECUTER_H

# include <sys/wait.h>
# include "libftio.h"
# include "minishell_structs.h"
# include "minishell_tools.h"
# include "minishell_buildins.h"

int		execute(t_shell *shell);
int		get_info_for_pipex(t_pipex_common *pipex_info, t_pipex *p_head,
			char **envp);
void	piping(t_pipex *p_head, t_pipex_common *pipex_info, int process,
			t_shell *shell);
void	close_pipes(int **pipes, int cur, int number_nodes);
int		first_process(t_pipex *p_head, t_pipex_common *pipex_info);
int		middle_process(t_pipex *p_head, t_pipex_common *pipex_info,
			int process);
int		last_process(t_pipex *p_head, t_pipex_common *pipex_info,
			int process);
int		check_before_fork(t_pipex *p_head);
int		builtin_main(t_pipex *p_head, t_shell *shell, int flag_builtin);
int		builtin_child(t_pipex *p_head, t_shell *shell,
			int flag_builtin);
int		check_builtins(t_pipex *p_head);
int		handle_outfile(t_pipex *p_head);
char	*get_cmd(t_pipex *p_head, char **paths);
int		open_files(t_pipex *p_head);
int		change_fds_child(t_pipex *p_head, t_pipex_common *pipex_info,
			int process);

#endif