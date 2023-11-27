/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_extras.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:21:59 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/27 18:55:27 by abektimi         ###   ########.fr       */
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
			tmp->pid = (*pid)[i];
			free((*pid));
			process_cmd(tmp, msc->dup_env, prev_output);
		}
		else if ((*pid)[i] > 0)
			main_process(tmp, prev_output);
		tmp = tmp->next;
		i++;
	}
}

//needed to shorten assemble_cmd()
//replaces the given cmd node's full_cmd array with a new one where
//the heredoc_name is added to the list of arguments
char	**append_heredoc_name(t_cmd **cmd)
{
	int		i;
	int		j;
	char	**ret;

	if (!cmd || !(*cmd))
		return (NULL);
	i = 0;
	while ((*cmd)->full_cmd[i] != NULL)
		i++;
	ret = ft_calloc((i + 2), sizeof(char *));
	if (!ret)
		return (NULL);
	j = -1;
	while (++j < i)
	{
		ret[j] = ft_strdup((*cmd)->full_cmd[j]);
		if (!ret[j])
			return (del_split(ret, j));
	}
	ret[j] = ft_strdup((*cmd)->heredoc_name);
	if (!ret[j])
		return (del_split(ret, j));
	ret[++j] = NULL;
	return (ret);
}
