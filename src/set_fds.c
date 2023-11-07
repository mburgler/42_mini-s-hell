/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 22:09:10 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/07 23:16:52 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	connect_fds(int c_fd0, int c_fd1, int *p_fd0, int *p_fd1)
{
	*p_fd0 = c_fd0;
	*p_fd1 = c_fd1;
}

int	close_all(t_cmd *cmd, int *cur_fds, int *prev_fds)
{
	if (close(cur_fds[0]) == -1 || close(cur_fds[1]) == -1)
		return (-1);
	if (cmd->prev != NULL)
	{
		if (close(prev_fds[0]) == -1 || close(prev_fds[1]) == -1)
			return (-1);
	}
	return (0);
}

int	set_file_desc(t_cmd *cmd, int *cur_fds, int *prev_fds)
{
	if (cmd->prev == NULL && cmd->next != NULL)
	{
		if (close(cur_fds[0]) == -1 || dup2(cur_fds[1], 1) == -1)
			return (-1);
	}
	else if (cmd->prev != NULL && cmd->next != NULL)
	{
		if (close(cur_fds[0]) == -1 || close(prev_fds[1]) == -1
			|| dup2(cur_fds[1], 1) == -1 || dup2(prev_fds[0], 0) == -1)
			return (-1);
	}
	else if (cmd->prev != NULL && cmd->next == NULL)
	{
		if (close(cur_fds[0]) == -1 || close(cur_fds[1]) == -1
			|| close(prev_fds[1]) == -1 || dup2(prev_fds[0], 0) == -1)
			return (-1);
	}
	return (0);
}
