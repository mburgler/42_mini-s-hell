/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 22:09:10 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/13 22:04:23 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//uses the dup2 syscall to make sure that I/O are passed through the pipeline,
//after which the obsolete file descriptors are closed
int	set_file_desc(t_cmd *cmd, int *p_fds, int *pr_op)
{
	if (cmd->prev == NULL && cmd->next != NULL)
	{
		if (dup2(p_fds[1], 1) == -1 || set_redir(cmd, p_fds, pr_op) == -1)
			return (-1);
		if (close(p_fds[0]) == -1 || close(p_fds[1]) == -1)
			return (-1);
	}
	else if (cmd->prev != NULL && cmd->next != NULL)
	{
		if (dup2(*pr_op, 0) == -1 || dup2(p_fds[1], 1) == -1
			|| set_redir(cmd, p_fds, pr_op) == -1)
			return (-1);
		if (close(p_fds[0]) == -1 || close(p_fds[1]) == -1)
			return (-1);
	}
	else if (cmd->prev != NULL && cmd->next == NULL)
	{
		if (dup2(*pr_op, 0) == -1 || set_redir(cmd, p_fds, pr_op) == -1)
			return (-1);
		if (close(p_fds[0]) == -1 || close(p_fds[1]) == -1)
			return (-1);
	}
	return (0);
}

//references the fd_in and fd_out file descriptors of the cmd node to
//make sure that the I/O is read/written to and from the appropriate source
int	set_redir(t_cmd *cmd, int *p_fds, int *pr_op)
{
	(void)p_fds;
	(void)pr_op;
	if (cmd->fd_in != 0)
	{
		if (dup2(cmd->fd_in, 0) == -1)
			return (-1);
		//FOR DEBUGGING: try closing fd_in if a child process leaks
	}
	if (cmd->fd_out != 1)
	{
		if (dup2(cmd->fd_out, 1) == -1)
			return (-1);
		//FOR DEBUGGING: try closing fd_out if a child process leaks
	}
	return (0);
}
