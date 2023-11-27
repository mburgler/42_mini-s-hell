/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extras.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:21:59 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/27 15:49:45 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//needed to shorten make_pipeline()
//loops through the list of commands in a pipeline, creating 
//child processes and p_fd pairs for each of them
void	fork_loop(t_msc *msc, t_cmd *tmp, int *prev_output, pid_t **pid)
{
	int	i;

	if (!msc || !tmp || !prev_output || !pid)
		return ;
	i = 0;
	while (tmp)
	{
		if (pipe(tmp->p_fds) == -1)
			free_msc_and_errno(msc, "Error in make_pipeline()");
		(*pid)[i] = fork();
		if ((*pid)[i] == -1)
			free_msc_and_errno(msc, "Error in make_pipeline()");
		else if ((*pid)[i] == 0)
		{
			free((*pid));
			process_cmd(tmp, msc->dup_env, prev_output);
		}
		else if ((*pid)[i] > 0)
			main_process(tmp, prev_output);
		tmp = tmp->next;
		i++;
	}
}
