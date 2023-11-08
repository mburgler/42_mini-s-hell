/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 22:09:10 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/08 18:13:35 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	set_file_desc(t_cmd *cmd, int *p_fds, int *prev_output)
{
	if (cmd->prev == NULL && cmd->next != NULL)
	{
		if (dup2(p_fds[1], 1) == -1)
			return (-1);
		if (close(p_fds[0]) == -1)
			return (-1);
	}
	else if (cmd->prev != NULL && cmd->next != NULL)
	{
		if (dup2(*prev_output, 0) == -1 || dup2(p_fds[1], 1) == -1)
			return (-1);
		if (close(p_fds[0]) == -1)
			return (-1);
	}
	else if (cmd->prev != NULL && cmd->next == NULL)
	{
		if (dup2(*prev_output, 0) == -1)
			return (-1);
		if (close(p_fds[0]) == -1 || close(p_fds[1]) == -1)
			return (-1);
	}
	return (0);
}

int	main_process(t_msc *msc, pid_t pid, int *p_fds, int *prev_output)
{
	(void)msc;
	if (close(p_fds[1]) == -1)
		return (-1);
	*prev_output = p_fds[0];
	wait_and_analyze(pid);
	return (0);
}
