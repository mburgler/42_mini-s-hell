/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 22:09:10 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/27 15:53:41 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//needed to shorten set_file_desc()
//closes pipe file descriptors inside single child processes
int	close_single_fds(t_cmd *cmd)
{
	if (!cmd)
		return (-1);
	if (!cmd->next && cmd->p_fds[0] != -1 && cmd->p_fds[1] != -1)
	{
		close(cmd->p_fds[0]);
		close(cmd->p_fds[1]);
	}
	return (0);
}

//sets up the necessary file descriptors so that child processes can
//read from/write to the correct fd
int	set_file_desc(t_cmd *cmd, int *p_fds, int *pr_op)
{
	if (cmd->next)
	{
		if (dup2(p_fds[1], STDOUT_FILENO) == -1)
			return (-1);
		close(p_fds[0]);
		close(p_fds[1]);
	}
	if (cmd->fd_in != 0)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			return (-1);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != 1)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			return (-1);
		close(cmd->fd_out);
	}
	if (*pr_op != 0)
		if (set_prev_output(pr_op) == -1)
			return (-1);
	if (close_single_fds(cmd) == -1)
		return (-1);
	return (0);
}

//closes all open fds inside the main process
void	close_all(t_cmd *cmds)
{
	if (!cmds)
		return ;
	while (cmds)
	{
		close(cmds->p_fds[0]);
		close(cmds->p_fds[1]);
		cmds = cmds->next;
	}
}

int	set_prev_output(int *pr_op)
{
	if (!pr_op)
		return (-1);
	if (dup2(*pr_op, STDIN_FILENO) == -1)
		return (-1);
	close(*pr_op);
	return (0);
}
