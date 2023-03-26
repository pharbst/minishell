/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_handle_fds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:22:34 by ccompote          #+#    #+#             */
/*   Updated: 2023/03/26 22:23:01 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_executer.h"

int	handle_outfile(t_pipex *p_head)
{
	t_redir_out	*tmp;

	tmp = p_head->out;
	while (tmp)
	{
		if (dup2(tmp->fd_right, tmp->fd_left) < 0)
			return (0);
		if (tmp->fd_right > 2)
			close(tmp->fd_right);
		tmp = tmp->next;
	}
	return (1);
}

// ctrl-c - sosatb
// ctrl-\ - sosatb

// ls >| llllogs
// ls > llllogs


//close all files?

//  /bin/ls
//  pointer of arg[0] being freed was not allocated

// < tmp 
//finishes before executor

// echo '$USER' must print $USER

// exit ""
// exit
// bash: exit: : numeric argument required
// ccompote@1-D-6 minishell % echo $?
// 255

// bash-3.2$ cat << hello
// > $USER
// > $NOVAR
// > $HOME
// > hello
// ccompote

// /Users/ccompote


// cat << lim ''
// > cds
// > lim
// cat: : No such file or directory

// command ""
// bash: : command not found, 127 error
// minishell new prompt, 137. should be parsed as empty command (finds this path to it /Users/ccompote/.brew/bin/ )

// "." / "/" 
//  new prompt, random error, isn't giving NULL to command because of ft_strchr("/.") in get_cmd

// ./ls
// bash: ./ls: No such file or directory
// minishell working

// export X="  A  B  "
// echo $X
// gives 0x0

// unset "$"

// arg[1]: Apple_Terminal

// /bin/echo $"HOME"$USER
// $HOMEccompote
// bash:
// HOMEccompote

//  /bin/echo "$"
// /var/folders/zz/zyxvpxvq6csfxvn_n000cf740033js/T/

//tests:
//builtins: 193 ok (wrong order), 232, 261, 265 ok, 
//269-273-279 (change findvar), 265-359 ok (mb wrong output fd)
//redirs: 48-54 ok, 60-64 ok (&& not handled), 77-99 ok (heredoc), 108, 114-132 ok (not handling)
//cmds: 11, 26 + 30 + 32 + 34 + 36 + 40 + 44
//vars: 8 - 10 ok, 12 - 22, 26-56, 79, 89-134
//correction: same
//paths: need to change path variable in child process


int	first_process(t_pipex *p_head, t_pipex_common *pipex_info)
{
	if (p_head->next)
	{
		if (dup2(pipex_info->pipes[0][1], STDOUT_FILENO) < 0)
			return (0);
	}
	if (p_head->fd_in)
	{
		if (dup2(p_head->fd_in, STDIN_FILENO) < 0)
			return (0);
		close(p_head->fd_in);
	}
	else if (p_head->in)
	{
		if (dup2(p_head->fd_in, STDIN_FILENO) < 0)
			return (0);
		close(p_head->fd_in);
	}
	if (p_head->out)
	{
		if (!handle_outfile(p_head))
			return (0);
	}
	return (1);
}

int	middle_process(t_pipex *p_head, t_pipex_common *pipex_info, int process)
{
	if (dup2(pipex_info->pipes[process - 1][0], STDIN_FILENO) < 0)
		return (0);
	if (dup2(pipex_info->pipes[process][1], STDOUT_FILENO) < 0)
		return (0);
	if (p_head->fd_in)
	{
		if (dup2(p_head->fd_in, STDIN_FILENO) < 0)
			return (0);
		close(p_head->fd_in);
	}
	if (p_head->out)
	{
		if (!handle_outfile(p_head))
			return (0);
	}
	return (1);
}

int	last_process(t_pipex *p_head, t_pipex_common *pipex_info, int process)
{
	if (p_head->fd_in)
	{
		if (dup2(p_head->fd_in, STDIN_FILENO) < 0)
			return (0);
		close(p_head->fd_in);
	}
	else
	{
		if (dup2(pipex_info->pipes[process - 1][0], STDIN_FILENO) < 0)
			return (0);
	}
	if (p_head->out)
	{
		if (!handle_outfile(p_head))
			return (0);
	}
	return (1);
}
