/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abektimi <abektimi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 01:48:41 by abektimi          #+#    #+#             */
/*   Updated: 2023/11/26 14:53:23 by abektimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//duplicates the first entry in each cmd node's full_cmd array into the
//cmd variable for easier handling in the executor later on
void	set_c_and_o(t_cmd *cmds)
{
	if (!cmds)
		return ;
	while (cmds)
	{
		if (cmds->full_cmd && cmds->full_cmd[0])
		{
			cmds->cmd = ft_strdup(cmds->full_cmd[0]);
			if (!cmds->cmd)
				free_msc_and_errno(cmds->msc, "Error in set_c_and_o()");
		}
		cmds = cmds->next;
	}
}

//isolates the command part from the path if a command is
//passed as such (e.g.: "/bin/ls", etc.)
void	isolate_cmd(t_cmd **cmd)
{
	int		i;
	int		j;
	char	*res;

	if (!cmd || !(*cmd))
		return ;
	i = 0;
	while ((*cmd)->cmd[i])
	{
		if ((*cmd)->cmd[i] == '/' && (*cmd)->cmd[i + 1])
			j = i + 1;
		i++;
	}
	i = 0;
	while ((*cmd)->cmd[j + i])
		i++;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return ;
	i = 0;
	while ((*cmd)->cmd[j])
		res[i++] = ((*cmd)->cmd[j++]);
	res[i] = '\0';
	free((*cmd)->cmd);
	(*cmd)->cmd = res;
}
